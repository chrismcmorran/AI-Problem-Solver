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

void getTimes(std::vector<int>* people, int numPeople)
{
	for (int i = 0; i < numPeople; ++i)
	{
		std::string input;
		while (true)
		{
			int time;
			std::cout << "How many time units does person " << i << " take to cross the bridge? ";
			std::cin >> input;

			std::stringstream ss(input);
			ss >> time;

			if (!ss)
				std::cout << "Invalid entry. ";
			else
			{
				people->push_back(time);
				break;
			}
		}
	}
	std::cout << std::endl;
}


int main()
{
	std::vector<int> peopleTimes;

	//std::cout << "How many people are trying to cross the bridge? ";
	getTimes(&peopleTimes, 6);

	BridgeState* initial = new BridgeState(&peopleTimes, LEFT);
	BridgeState* goal = new BridgeState(&peopleTimes, RIGHT);

	AI::Puzzle bridgePuzzle(initial, goal, AI::BREADTH_FIRST);
	bridgePuzzle.solve();
	return 0;
}