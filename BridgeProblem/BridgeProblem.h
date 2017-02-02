#ifndef _BRIDGE_PROBLEM_H
#define _BRIDGE_PROBLEM_H

#include <vector>
#include "../LibAI/Problem.h"
#include "../LibAI/State.h"

namespace BridgeProblem {
	/* The bridge problem:

	   A number of people must move over a narrow bridge at night. The bridge can
	   only hold two people at a time and a torch has to be used to cross the bridge.
	   Each person takes a certain amount of time to cross the bridge. When two persons
	   are crossing the bridge together, they both move at the pace dictated by the
	   slower person. The task is get the group across the bridge in the minimum time. */
	class Problem : public AI::Problem {
		public:
			Problem(AI::SearchType searchType);

		private:
			std::vector<int> peopleTimes;

			virtual AI::State* genInitialState();
			virtual AI::State* genGoalState();
	};
}

#endif
