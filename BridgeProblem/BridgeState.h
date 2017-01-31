#ifndef _BRIDGE_STATE_H
#define _BRIDGE_STATE_H

#include <vector>
#include "../LibAI/State.h"

namespace BridgeProblem {
	class BridgeAction;

	enum BridgeSide {
		LEFT,
		RIGHT
	};

	// A state of the bridge problem
	class BridgeState : public AI::State {
		public:
			BridgeState(std::vector<int>* peopleTimes, BridgeSide startingSide);
			BridgeState(const BridgeState &bs);
			~BridgeState();

			BridgeSide getPersonSide(int i) const;
			int getPersonTime(int i) const;
			void setPersonSide(int i, BridgeSide bs);
			BridgeSide getTorchSide() const;
			void setTorchSide(BridgeSide bs);

			virtual unsigned long getStateCode() const;
			virtual void getActions(std::vector<AI::Action*>& actions) const;
			virtual std::string describe() const;

		private:
			const std::vector<int>* peopleTimes;
			BridgeSide* peopleSides;
			BridgeSide torchSide;
	};
}

#endif
