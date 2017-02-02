#ifndef _PROBLEM_H
#define _PROBLEM_H

#include <ostream>
#include <set>
#include "State.h"
#include "SearchNode.h"
#include "Fringe.h"

namespace AI {
	enum SearchType {
		BREADTH_FIRST,
		DEPTH_FIRST
	};

	// Allows std::set of pointers to be sorted using an overridden operator<
	template <typename T>
	struct PointerComp
	{
		bool operator ()(const T* a, const T* b) const
		{
		   return *a < *b;
		}
	};

	// A problem to be solved using AI techniques
	class Problem {
		public:
			Problem(SearchType searchType);
			virtual ~Problem();
			void solve();

		private:
			Fringe<SearchNode*>* fringe;
			std::set<const State*, PointerComp<State>> seenStates;
			std::set<SearchNode*> allocatedNodes;
			const State* goalState;

			void expand(SearchNode* node);
			bool goalReached(const State* currState);
			virtual State* genInitialState() = 0;
			virtual State* genGoalState() = 0;
	};
}

#endif
