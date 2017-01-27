#ifndef _PUZZLE_H
#define _PUZZLE_H

#include <ostream>
#include <queue>  // For now
#include <set>
#include "State.h"
#include "SearchNode.h"

namespace AI {
	template <typename T>
	// Allows std::set of pointers to be sorted using an overridden operator<
	struct PointerComp
	{
		bool operator ()(const T* a, const T* b) const
		{
		   return *a < *b;
		}
	};

	// A problem to be solved using AI techniques
	class Puzzle {
		public:
			Puzzle(State* initialState, State* goalState);
			~Puzzle();
			void solve();

		private:
			std::queue<SearchNode*> fringe;
			std::set<const State*, PointerComp<State>> seenStates;
			const State* goalState;

			void expand(SearchNode* node);
			bool goalReached(const State* currState);
	};
}

#endif
