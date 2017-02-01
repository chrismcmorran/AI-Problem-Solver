#include <algorithm>
#include <cstring>
#include <sstream>
#include "TileAction.h"
#include "TileState.h"

using namespace TileProblem;

TileState::TileState(short boardWidth, short boardHeight, TileStateType stateType)
{
	int totalTiles = boardHeight * boardWidth;
	char num = 1;

	this->boardWidth = boardWidth;
	this->boardHeight = boardHeight;

	board = new short[totalTiles];
	for (int i = 0; i < totalTiles; ++i)
	{
		board[i] = num;
		num = ((num + 1) % totalTiles);
	}

	if (stateType == SHUFFLED)
	{
		srand(time(NULL));
		std::random_shuffle(&board[0], &board[totalTiles]);
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


void TileState::setTileValue(short row, short col, char v)
{
	board[col + (row * boardWidth)] = v;
}

unsigned long TileState::getStateCode() const
{
	unsigned long code = 1;
	int totalTiles = boardWidth * boardHeight;
	for (int i = 0; i < totalTiles; ++i)
		code += (code * 31) + board[i];
	return code;
}

void TileState::getActions(std::vector<AI::Action*>& actions) const
{
	for (short row = 0; row < boardHeight; ++row)
	{
		for (short col = 0; col < boardWidth; ++col)
		{
			if (getTileValue(row, col) == 0)
			{
				// Found blank tile
				// TODO: diagonal and horse move
				if (col > 0)
					actions.push_back(new TileAction(row, col, row, col-1));
				if (col < boardWidth-1)
					actions.push_back(new TileAction(row, col, row, col+1));
				if (row > 0)
					actions.push_back(new TileAction(row, col, row-1, col));
				if (row < boardHeight-1)
					actions.push_back(new TileAction(row, col, row+1, col));
				break;
			}
		}
	}

	/*BridgeSide dest = (torchSide == LEFT) ? RIGHT : LEFT;
	std::vector<int> people;
	unsigned int i;

	// Which people can be moved (who's on the same side as the torch)?
	for (i = 0; i < peopleTimes->size(); ++i)
	{
		if (peopleSides[i] == torchSide)
			people.push_back(i);
	}

	// Generate all possible moves that can be made from the current state
	genMoves(actions, people, dest, 0, -1);
	for (i = 0; i < people.size(); ++i)
	{
		int p2 = people.at(i);
		genMoves(actions, people, dest, i+1, p2);
	}*/
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
