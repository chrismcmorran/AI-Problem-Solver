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
			SearchNode(const State* state, int cost=0, Action* generatingAction=NULL, SearchNode* parent=NULL);
			~SearchNode();
			SearchNode* getParent() const;
			void setParent(SearchNode* parent);
			const State* getState() const;
			Action* getGeneratingAction() const;
			void setGeneratingAction(Action* action);
			int getCostFromRoot() const;
			void setCostFromRoot(int cost);

		private:
			SearchNode* parent;
			const State* state;
			Action* generatingAction;
			int costFromRoot;
	};
}

#endif
