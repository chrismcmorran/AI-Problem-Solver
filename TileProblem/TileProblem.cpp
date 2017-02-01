#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "../LibAI/Puzzle.h"
#include "TileState.h"

using namespace TileProblem;

/* The tile problem:

   An mxn grid contains tiles with the numbers 1..(mxn)-1 through ‘8’ on them.
   Initially these tiles are in a random order. One space is left blank. The
   goal is to arrange the tiles in the correct order.

   -Any tile that is adjacent or diagonal to the blank space can slide into it
   -Two non-blank tiles can be swapped as per the chess "horse move" */

static int getInt(std::string prompt, int min)
{
	// Get int from user and validate input
	std::string input;
	int i;

	while (true)
	{
		std::cout << prompt;
		std::cin >> input;
		std::stringstream ss(input);
		ss >> i;

		if (ss.fail() || i < min)
			std::cout << "Invalid input. ";
		else
			return i;
	}
}

int main()
{
	short height = getInt("What is the board height? ", 1);
	short width = getInt("What is the board width? ", 1);
	TileState* initial = new TileState(width, height);
	TileState* goal = new TileState(width, height);

	// Populate board
	for (short row = 0; row < height; ++row)
	{
		for (short col = 0; col < width; ++col)
		{
			std::stringstream ss;
			short val;
			ss << "Which tile is at (" << row << "," << col << ")? ";
			initial->setTileValue(row, col, getInt(ss.str(), 0));
		}
	}
	std::cout << std::endl;

	AI::Puzzle tilePuzzle(initial, goal, AI::BREADTH_FIRST);
	tilePuzzle.solve();
	return 0;
}