#include <climits>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../LibAI/Util.h"

#include "BridgeProblem.h"
#include "BridgeState.h"

using namespace BridgeProblem;

std::vector<int> peopleTimes;

Problem::Problem(AI::SearchType searchType) : AI::Problem(searchType)
{
	int numPeople = AI::Util::getInt("How many people are trying to cross the bridge? ", 0, BridgeState::getMaxPeople());
	for (int i = 0; i < numPeople; ++i)
	{
		std::stringstream ss;
		ss << "How many time units does person " << i << " take to cross the bridge? ";
		peopleTimes.push_back(AI::Util::getInt(ss.str(), INT_MIN, INT_MAX));
		ss.clear();
	}
	std::cout << std::endl;
}

AI::State* Problem::genInitialState()
{
	return new BridgeState(&peopleTimes, LEFT);
}

AI::State* Problem::genGoalState()
{
	return new BridgeState(&peopleTimes, RIGHT);
}
