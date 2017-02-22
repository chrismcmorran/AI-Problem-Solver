#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../LibAI/Util.h"

#include "TilePuzzle.h"
#include "TileState.h"

using namespace TilePuzzle;

Puzzle::Puzzle(AI::SearchType searchType) : AI::Puzzle(searchType)
{
	short height, width;

	if (searchType == AI::A_STAR)
	{
		int heurNum = AI::Util::getInt("Which heuristic function do you want to use?\n"
								       "1) Misplaced tile count\n"
								       "2) Manhattan distance\n"
									   "3) Average of (1) and (2)\n", 1, 3);
		TileState::setHeuristic((TileHeuristic)heurNum);
		std::cout << std::endl;
	}

	height = AI::Util::getInt("What is the board height? ", 1, SHRT_MAX);
	width = AI::Util::getInt("What is the board width? ", 1, SHRT_MAX);
	std::cout << std::endl;
	TileState::setBoardDimensions(width, height);
}

AI::State* Puzzle::genInitialState() const
{
	TileState* initial = new TileState();

	// Populate board
	short width = TileState::getBoardWidth(), height = TileState::getBoardHeight();
	for (short row = 0; row < height; ++row)
	{
		for (short col = 0; col < width; ++col)
		{
			std::stringstream ss;
			ss << "Which tile is at (" << row << "," << col << ")? ";
			initial->setTileValue(row, col, AI::Util::getInt(ss.str(), 0, (width * height) - 1));
		}
	}
	std::cout << std::endl;
	return initial;
}

AI::State* Puzzle::genGoalState() const
{
	return new TileState();
}
