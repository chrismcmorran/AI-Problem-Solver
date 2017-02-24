#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../../LibAI/Util.h"

#include "BridgePuzzle.h"
#include "BridgeState.h"

using namespace BridgePuzzle;

Puzzle::Puzzle(AI::SearchType searchType) : AI::Puzzle(searchType)
{
	int numPeople;


	if (searchType == AI::A_STAR)
	{
		int heurNum = AI::Util::getInt("Which heuristic function do you want to use?\n"
								       "1) Number of people who have yet to cross\n"
								       "2) Sum of times of people who have already crossed\n"
									   "3) Average of (1) and (2)\n", 1, 3);
		BridgeState::setHeuristic((BridgeHeuristic)heurNum);
		std::cout << std::endl;
	}

	numPeople = AI::Util::getInt("How many people are trying to cross the bridge? ", 0, BridgeState::getMaxPeople());
	std::cout << std::endl;
	for (int i = 0; i < numPeople; ++i)
	{
		std::stringstream ss;
		ss << "How many time units does person " << i << " take to cross the bridge? ";
		peopleTimes.push_back(AI::Util::getInt(ss.str(), INT_MIN, INT_MAX));
		ss.clear();
	}
	BridgeState::setPeopleTimes(&peopleTimes);
	std::cout << std::endl;
}

AI::State* Puzzle::genInitialState() const
{
	return new BridgeState(LEFT);
}

AI::State* Puzzle::genGoalState() const
{
	return new BridgeState(RIGHT);
}
