#ifndef _BRIDGE_ACTION_H
#define _BRIDGE_ACTION_H

#include "../LibAI/Action.h"
#include "BridgeState.h"
#include <string>

namespace BridgeProblem {
	/* An action that can be performed on a state of the
	   bridge problem (i.e., moving people across) */
	class BridgeAction : public AI::Action {
		public:
			BridgeAction(BridgeSide dest, int p1, int p2=-1);
			virtual int execute(const AI::State* inState, AI::State** outState);
			virtual std::string describe();

		private:
			int person1, person2;
			BridgeSide destSide;
	};
}

#endif
