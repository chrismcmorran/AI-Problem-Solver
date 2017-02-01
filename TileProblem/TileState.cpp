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

short TileState::getTileValue(short x, short y) const
{
	return board[x + (y * boardWidth)];
}


void TileState::setTileValue(short x, short y, char v)
{
	board[x + (y * boardWidth)] = v;
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
	for (short y = 0; y < boardHeight; ++y)
	{
		for (short x = 0; x < boardWidth; ++x)
		{
			if (getTileValue(x, y) == 0)
			{
				// Found blank tile
				// TODO: diagonal and horse move
				if (x > 0)
					actions.push_back(new TileAction(x, y, x-1, y));
				if (x < boardWidth-1)
					actions.push_back(new TileAction(x, y, x+1, y));
				if (y > 0)
					actions.push_back(new TileAction(x, y, x, y-1));
				if (y < boardHeight-1)
					actions.push_back(new TileAction(x, y, x, y+1));
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
	for (short y = 0; y < boardHeight; ++y)
	{
		for (short x = 0; x < boardWidth; ++x)
			ss << " ---";
		ss << std::endl;
		for (short x = 0; x < boardWidth; ++x)
		{
			int val = getTileValue(x, y);
			ss << "| ";
			if (val == 0)
				ss << " ";
			else
				ss << val;
			ss << " ";
		}
		ss << "|" << std::endl;
	}
	for (short x = 0; x < boardWidth; ++x)
			ss << " ---";
	return ss.str();
}
