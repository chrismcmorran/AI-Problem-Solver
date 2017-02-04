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
			Fringe* fringe;
			std::set<const State*, PointerComp<State>> seenStates;
			std::set<SearchNode*> allocatedNodes;
			const State* goalState;
			SearchType searchType;

			void expand(SearchNode* node);
			void checkLeafNode(SearchNode* node);
			bool goalReached(const State* currState);
			virtual State* genInitialState() = 0;
			virtual State* genGoalState() = 0;
	};
}

#endif
