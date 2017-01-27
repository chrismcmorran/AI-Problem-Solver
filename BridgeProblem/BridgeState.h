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

	// A state of the bridge problem
	class BridgeState : public AI::State {
		public:
			BridgeState(BridgeSide startingSide);
			BridgeState(const BridgeState &bs);

			BridgeSide getPersonSide(int i) const;
			void setPersonSide(int i, BridgeSide bs);
			BridgeSide getTorchSide() const;
			void setTorchSide(BridgeSide bs);

			virtual int getStateCode() const;
			virtual void getActions(std::vector<AI::Action*>& actions) const;
			virtual std::string describe() const;

		private:
			BridgeSide peopleSides[6];
			BridgeSide torchSide;
	};
}

#endif
