/*
   COMP 4106 - Assignment 1
   Matt Penny
*/

#include <iostream>
#include "../LibAI/Puzzle.h"
#include "../LibAI/Util.h"
#include "BridgePuzzle/BridgePuzzle.h"
#include "TilePuzzle/TilePuzzle.h"

int main()
{
	int puzzNum, searchNum;
	AI::Puzzle* puzzle;

	puzzNum = AI::Util::getInt("Which puzzle do you want to solve?\n"
							   "1) Bridge puzzle\n"
							   "2) Tile puzzle\n", 1, 2);
	std::cout << std::endl;
	searchNum = AI::Util::getInt("Which search strategy do you want to use?\n"
								 "1) Breadth-first search\n"
								 "2) Depth-first search\n"
								 "3) A*\n", 1, 3);
	std::cout << std::endl;

	if (puzzNum == 1)
		puzzle = new BridgePuzzle::Puzzle((AI::SearchType)searchNum);
	else
		puzzle = new TilePuzzle::Puzzle((AI::SearchType)searchNum);
	puzzle->solve();
	delete puzzle;
	return 0;
}
