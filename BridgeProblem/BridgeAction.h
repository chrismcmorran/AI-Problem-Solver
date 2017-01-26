#ifndef _BRIDGE_ACTION_H
#define _BRIDGE_ACTION_H

#include "../AIUtils/Action.h"
#include "BridgeState.h"
#include <string>

namespace BridgeProblem {
	class BridgeAction : public AIUtils::Action {
		public:
			BridgeAction(BridgeSide dest, int p1, int p2=-1);
			virtual BridgeState* execute(BridgeState& state);
			virtual std::string describe();

		private:
			int person1, person2;
			BridgeSide destSide;
	};
}

#endif
