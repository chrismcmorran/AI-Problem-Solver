#ifndef _BRIDGE_STATE_H
#define _BRIDGE_STATE_H

#include "../AIUtils/State.h"
#include <vector>

namespace BridgeProblem {
	enum BridgeSide {
		LEFT,
		RIGHT
	};

	class BridgeAction;

	class BridgeState : public AIUtils::State {
		public:
			BridgeState();
			BridgeState(const BridgeState &bs);

			BridgeSide getPersonSide(int i);
			void setPersonSide(int i, BridgeSide bs);
			BridgeSide getTorchSide();
			void setTorchSide(BridgeSide bs);

			static bool compare(const BridgeState& a, const BridgeState& b);
			virtual void getActions(std::vector<AIUtils::Action*>& actions);

		private:
			BridgeSide peopleSides[6];
			BridgeSide torchSide;
	};
}

#endif
