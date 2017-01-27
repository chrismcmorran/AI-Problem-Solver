#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "../AIUtils/Puzzle.h"
#include "BridgeState.h"

using namespace BridgeProblem;

/* The bridge problem:

   A number of people must move over a narrow bridge at night. The bridge can
   only hold two people at a time and a torch has to be used to cross the bridge.
   Each person takes a certain amount of time to cross the bridge. When two persons
   are crossing the bridge together, they both move at the pace dictated by the
   slower person. The task is get the group across the bridge in the minimum time. */

static int getInt(std::string prompt)
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

		if (ss.fail())
			std::cout << "Invalid input. ";
		else
			return i;
	}
}

int main()
{
	std::vector<int> peopleTimes;
	int numPeople = getInt("How many people are trying to cross the bridge? ");
	for (int i = 0; i < numPeople; ++i)
	{
		std::stringstream ss;
		ss << "How many time units does person " << i << " take to cross the bridge? ";
		peopleTimes.push_back(getInt(ss.str()));
		ss.clear();
	}
	std::cout << std::endl;

	BridgeState* initial = new BridgeState(&peopleTimes, LEFT);
	BridgeState* goal = new BridgeState(&peopleTimes, RIGHT);

	AI::Puzzle bridgePuzzle(initial, goal, AI::BREADTH_FIRST);
	bridgePuzzle.solve();
	return 0;
}