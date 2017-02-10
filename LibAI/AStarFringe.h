#ifndef _A_STAR_FRINGE_CONTAINER_H
#define _A_STAR_FRINGE_CONTAINER_H

#include <queue>
#include <vector>
#include "Fringe.h"
#include "SearchNode.h"

namespace AI {
	struct HeuristicComp {
		bool operator ()(const SearchNode* a, const SearchNode* b) const
		{
			return (a->getCostFromRoot() + a->getState()->estimateGoalDist()) >
				   (b->getCostFromRoot() + b->getState()->estimateGoalDist());
		}
	};

	/* Container for the fringe which facilitates A* search (a priority queue) */
	class AStarFringe : public Fringe {
		private:
			std::priority_queue<SearchNode*, std::vector<SearchNode*>, HeuristicComp> container;

		public:
			virtual void push(SearchNode* val);
			virtual void pop();
			virtual SearchNode* front();
			virtual bool empty();
	};
}

#endif