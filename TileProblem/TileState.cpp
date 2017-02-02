#include <cstring>
#include <sstream>
#include "TileAction.h"
#include "TileState.h"

using namespace TileProblem;

TileState::TileState(short boardWidth, short boardHeight)
{
	int totalTiles = boardHeight * boardWidth;
	char num = 1;

	this->boardWidth = boardWidth;
	this->boardHeight = boardHeight;

	// Goal state
	board = new short[totalTiles];
	for (int i = 0; i < totalTiles; ++i)
	{
		board[i] = num;
		num = ((num + 1) % totalTiles);
	}
}

TileState::TileState(const TileState &ts)
{
	int totalTiles = ts.boardHeight * ts.boardWidth;
	boardWidth = ts.boardWidth;
	boardHeight = ts.boardHeight;
	board = new short[totalTiles];
	std::memcpy(board, ts.board, sizeof(short) * totalTiles);
}

TileState::~TileState()
{
	delete[] board;
}

short TileState::getTileValue(short row, short col) const
{
	return board[col + (row * boardWidth)];
}


void TileState::setTileValue(short row, short col, short v)
{
	board[col + (row * boardWidth)] = v;
}

unsigned long TileState::getStateCode() const
{
	unsigned long code = 1;
	int totalTiles = boardWidth * boardHeight;
	for (int i = 0; i < totalTiles; ++i)
		code += (code * 37) + board[i];
	return code;
}

static short KNIGHT_MOVE_OFFSETS[8][2] = {
	{-2, -1},
	{-2, 1},
	{2, -1},
	{2, 1},
	{-1, -2},
	{-1, 2},
	{1, -2},
	{1, 2}
};

void TileState::getActions(std::vector<AI::Action*>& actions) const
{
	for (short row = 0; row < boardHeight; ++row)
	{
		for (short col = 0; col < boardWidth; ++col)
		{
			if (getTileValue(row, col) == 0)
			{
				// Found blank tile
				if (col > 0)
					actions.push_back(new TileAction(row, col, row, col-1));
				if (col < boardWidth-1)
					actions.push_back(new TileAction(row, col, row, col+1));
				if (row > 0)
				{
					// Top, top-left, and top-right
					actions.push_back(new TileAction(row, col, row-1, col));
					if (col > 0)
						actions.push_back(new TileAction(row, col, row-1, col-1));
					if (col < boardWidth-1)
						actions.push_back(new TileAction(row, col, row-1, col+1));
				}
				if (row < boardHeight-1)
				{
					// Bottom, bottom-left, and bottom-right
					actions.push_back(new TileAction(row, col, row+1, col));
					if (col > 0)
						actions.push_back(new TileAction(row, col, row+1, col-1));
					if (col < boardWidth-1)
						actions.push_back(new TileAction(row, col, row+1, col+1));
				}
				break;
			}
			else
			{
				// L-shaped "knight" moves for non-blank tiles
				for (short i = 0; i < 8; ++i)
				{
					short newRow = row + KNIGHT_MOVE_OFFSETS[i][0];
					short newCol = col + KNIGHT_MOVE_OFFSETS[i][1];
					short val = getTileValue(newRow, newCol);
					if (newRow > 0 && newRow < boardHeight && newCol > 0 && newCol < boardWidth && val != 0)
						actions.push_back(new TileAction(row, col, newRow, newCol));
				}
			}
		}
	}
}

std::string TileState::describe() const
{
	// Draws the current state
	std::ostringstream ss;
	for (short row = 0; row < boardHeight; ++row)
	{
		for (short col = 0; col < boardWidth; ++col)
			ss << " ---";
		ss << std::endl;
		for (short col = 0; col < boardWidth; ++col)
		{
			int val = getTileValue(row, col);
			ss << "| ";
			if (val == 0)
				ss << " ";
			else
				ss << val;
			ss << " ";
		}
		ss << "|" << std::endl;
	}
	for (short col = 0; col < boardWidth; ++col)
			ss << " ---";
	return ss.str();
}
