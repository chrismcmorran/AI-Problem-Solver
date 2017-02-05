#include <cstring>
#include <cmath>
#include <sstream>
#include "TileAction.h"
#include "TileState.h"

using namespace TileProblem;

short TileState::boardWidth = 0, TileState::boardHeight = 0;
TileHeuristic TileState::heuristic = MISPLACED_TILES;

void TileState::setBoardDimensions(short width, short height)
{
	boardWidth = width;
	boardHeight = height;
}

void TileState::setHeuristic(TileHeuristic heuristic)
{
	TileState::heuristic = heuristic;
}

short TileState::getBoardWidth()
{
	return boardWidth;
}

short TileState::getBoardHeight()
{
	return boardHeight;
}

TileState::TileState()
{
	int totalTiles = boardHeight * boardWidth;
	short num = 1;

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

					if (newRow > 0 && newRow < boardHeight && newCol > 0 && newCol < boardWidth)
					{
						short val = getTileValue(newRow, newCol);
						if (val != 0)
							actions.push_back(new TileAction(row, col, newRow, newCol));
					}
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

int TileState::estimateGoalDist() const
{
	int numMisplaced = 0, manhattan = 0;
	int totalTiles = boardHeight * boardWidth;

	short num = 1;
	for (int i = 0; i < totalTiles; ++i)
	{
		// Is tile misplaced?
		if (board[i] != num)
		{
			// Heuristic 1: number of tiles out of place
			if (heuristic == AVERAGE || heuristic == MISPLACED_TILES)
				++numMisplaced;

			// Heuristic 2: manhattan distance
			if (heuristic == AVERAGE || heuristic == MANHATTAN_DISTANCE)
			{
				short curRow = i / boardWidth;
				short curCol = i % boardWidth;
				short expRow, expCol;

				if (board[i] == 0)
				{
					// Special case
					expRow = boardWidth-1;
					expCol = boardHeight-1;
				}
				else
				{
					expRow = board[i] / boardWidth;
					expCol = board[i] % boardWidth;
				}
				manhattan += std::abs(curRow - expRow) + std::abs(curCol - expCol);
			}
		}
		num = ((num + 1) % totalTiles);
	}

	if (heuristic == MISPLACED_TILES)
		return numMisplaced;
	else if (heuristic == MANHATTAN_DISTANCE)
		return manhattan;
	else  // Average
		return (numMisplaced + manhattan)/2;
}
