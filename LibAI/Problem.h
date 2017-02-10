#ifndef _PROBLEM_H
#define _PROBLEM_H

#include <ostream>
#include <set>
#include "State.h"
#include "SearchNode.h"
#include "Fringe.h"

namespace AI {
	enum SearchType {
		BREADTH_FIRST = 1,
		DEPTH_FIRST,
		A_STAR
	};

	struct NodeComp
	{
		bool operator()(const SearchNode* a, const SearchNode* b) const
		{
			return *(a->getState()) < *(b->getState());
		}
	};

	// A problem to be solved using AI techniques
	class Problem {
		public:
			Problem(SearchType searchType);
			virtual ~Problem();
			void solve();

		private:
			Fringe* fringe;
			std::set<SearchNode*, NodeComp> closed;
			const State* goalState;
			SearchType searchType;

			void expand(SearchNode* node);
			bool goalReached(const State* currState);
			void cleanup();
			virtual State* genInitialState() = 0;
			virtual State* genGoalState() = 0;
	};
}

#endif
