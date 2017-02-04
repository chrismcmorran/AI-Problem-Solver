#ifndef _BREADTH_FIRST_FRINGE_CONTAINER_H
#define _BREADTH_FIRST_FRINGE_CONTAINER_H

#include <queue>
#include "Fringe.h"

namespace AI {
	/* Container for the fringe which facilitates breadth-first search (a queue) */
	class BreadthFirstFringe : public Fringe {
		private:
			std::queue<SearchNode*> container;

		public:
			virtual void push(SearchNode* val);
			virtual void pop();
			virtual SearchNode* front();
			virtual bool empty();
	};
}

#endif