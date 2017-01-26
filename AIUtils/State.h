#ifndef _STATE_H
#define _STATE_H

#include <vector>
#include "Action.h"

namespace AIUtils {
	class State {
		public:
			virtual void getActions(std::vector<Action*>& actions) = 0;
			virtual std::string describe() = 0;
	};
}

#endif
