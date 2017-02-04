#ifndef _DEPTH_FIRST_FRINGE_CONTAINER_H
#define _DEPTH_FIRST_FRINGE_CONTAINER_H

#include <stack>
#include "Fringe.h"

namespace AI {
	/* Container for the fringe which facilitates depth-first search (a stack) */
	class DepthFirstFringe : public Fringe {
		private:
			std::stack<SearchNode*> container;

		public:
			virtual void push(SearchNode* val);
			virtual void pop();
			virtual SearchNode* front();
			virtual bool empty();
	};
}

#endif