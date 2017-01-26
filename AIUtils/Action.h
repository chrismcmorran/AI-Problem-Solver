#ifndef _ACTION_H
#define _ACTION_H

#include <vector>
/*#include "State.h"*/

namespace AIUtils {
	class Action {
		public:
			//virtual State* execute(State& state) = 0;
			virtual std::string describe() = 0;
	};
}

#endif
