#ifndef _PUZZLE_H
#define _PUZZLE_H

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

	// A puzzle to be solved using AI techniques
	class Puzzle {
		public:
			Puzzle(SearchType searchType);
			virtual ~Puzzle();
			void solve();

		private:
			Fringe* fringe;
			std::set<SearchNode*, NodeComp> closed;
			const State* goalState;
			SearchType searchType;

			void generateSuccessors(SearchNode* node);
			void cleanup();
			virtual State* genInitialState() const = 0;
			virtual State* genGoalState() const = 0;
	};
}

#endif
