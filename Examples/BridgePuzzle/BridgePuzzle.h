#ifndef _BRIDGE_PUZZLE_H
#define _BRIDGE_PUZZLE_H

#include <vector>
#include "../../LibAI/Puzzle.h"
#include "../../LibAI/State.h"

namespace BridgePuzzle {
	/* The bridge puzzle:

	   A number of people must move over a narrow bridge at night. The bridge can
	   only hold two people at a time and a torch has to be used to cross the bridge.
	   Each person takes a certain amount of time to cross the bridge. When two persons
	   are crossing the bridge together, they both move at the pace dictated by the
	   slower person. The task is get the group across the bridge in the minimum time. */
	class Puzzle : public AI::Puzzle {
		public:
			Puzzle(AI::SearchType searchType);

		private:
			std::vector<int> peopleTimes;

			virtual AI::State* genInitialState() const;
			virtual AI::State* genGoalState() const;
	};
}

#endif
