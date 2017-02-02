/*
   COMP 4106 - Assignment 1
   Matt Penny
*/

#include <iostream>
#include "../LibAI/Problem.h"
#include "../LibAI/Util.h"
#include "../BridgeProblem/BridgeProblem.h"
#include "../TileProblem/TileProblem.h"

int main()
{
	int probNum, searchNum;
	AI::Problem* problem;
	AI::SearchType searchType;
	
	probNum = AI::Util::getInt("Which problem do you want to solve?\n"
							   "1) Bridge problem\n"
							   "2) Tile problem\n", 1, 2);
	std::cout << std::endl;
	searchNum = AI::Util::getInt("Which search strategy do you want to use?\n"
								 "1) Breadth-first search\n"
								 "2) Depth-first search\n", 1, 2);
	std::cout << std::endl;
	searchType = (searchNum == 1) ? AI::BREADTH_FIRST : AI::DEPTH_FIRST;
	if (probNum == 1)
		problem = new BridgeProblem::Problem(searchType);
	else
		problem = new TileProblem::Problem(searchType);
	problem->solve();
	delete problem;
	return 0;
}