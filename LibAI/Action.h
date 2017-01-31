#ifndef _ACTION_H
#define _ACTION_H

#include <vector>
#include "State.h"

namespace AI {
	// An action that can be performed on a state
	class Action {
		public:
			// Returns the cost of the action
			virtual int execute(const State* inState, State** outState) = 0;
			virtual std::string describe() = 0;
	};
}

#endif
