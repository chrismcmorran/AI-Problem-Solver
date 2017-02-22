#ifndef _FRINGE_H
#define _FRINGE_H

#include "SearchNode.h"

namespace AI {
	/* Container for the fringe. Implementation will affect
	   state space search behavior */
	class Fringe {
		public:
			virtual void push(SearchNode* val) = 0;
			virtual void pop() = 0;
			virtual SearchNode* front() = 0;
			virtual bool empty() = 0;
			virtual ~Fringe() {};
	};
}

#endif
