#ifndef _BRIDGE_STATE_H
#define _BRIDGE_STATE_H

#include <vector>
#include "../../LibAI/State.h"

namespace BridgePuzzle {
	class BridgeAction;

	enum BridgeSide {
		LEFT,
		RIGHT
	};

	enum BridgeHeuristic {
		LEFT_PEOPLE = 1,
		RIGHT_TIMES,
		AVERAGE
	};

	// A state of the bridge puzzle
	class BridgeState : public AI::State {
		public:
			BridgeState(BridgeSide startingSide);
			BridgeState(const BridgeState &bs);
			virtual ~BridgeState();

			BridgeSide getPersonSide(int i) const;
			int getPersonTime(int i) const;
			void setPersonSide(int i, BridgeSide bs);
			BridgeSide getTorchSide() const;
			void setTorchSide(BridgeSide bs);

			virtual unsigned long getStateCode() const;
			virtual void getActions(std::vector<AI::Action*>& actions) const;
			virtual std::string describe() const;
			virtual int heuristicValue() const;
			static int getMaxPeople();
			static void setHeuristic(BridgeHeuristic heuristic);
			static void setPeopleTimes(std::vector<int>* peopleTimes);

		private:
			static const std::vector<int>* peopleTimes;
			BridgeSide* peopleSides;
			BridgeSide torchSide;
			static BridgeHeuristic heuristic;
	};
}

#endif
