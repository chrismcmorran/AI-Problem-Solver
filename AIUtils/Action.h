#ifndef _ACTION_H
#define _ACTION_H

#include <vector>
#include "State.h"

namespace AI {
	// An action that can be performed on a state
	class Action {
		public:
			virtual const State* execute(const State* state) = 0;
			virtual std::string describe() = 0;
	};
}

#endif
