#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../LibAI/Util.h"

#include "TileProblem.h"
#include "TileState.h"

using namespace TileProblem;

Problem::Problem(AI::SearchType searchType) : AI::Problem(searchType)
{
	height = AI::Util::getInt("What is the board height? ", 1, SHRT_MAX);
	width = AI::Util::getInt("What is the board width? ", 1, SHRT_MAX);
}

AI::State* Problem::genInitialState()
{
	TileState* initial = new TileState(width, height);

	// Populate board
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

AI::State* Problem::genGoalState()
{
	return new TileState(width, height);
}