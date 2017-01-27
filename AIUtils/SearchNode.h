#ifndef _SEARCH_NODE_H
#define _SEARCH_NODE_H

#include <vector>
#include "State.h"
#include "Action.h"

namespace AI {
	/* Node containing a state in a problem's state space and data required to
	   construct a path from the initial state */
	class SearchNode {
		public:
			SearchNode(const State* state, Action* generatingAction=NULL, SearchNode* parent=NULL);
			SearchNode* getParent();
			const State* getState();
			Action* getGeneratingAction();

		private:
			SearchNode* parent;
			const State* state;
			Action* generatingAction;
	};
}

#endif