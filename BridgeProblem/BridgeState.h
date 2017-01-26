#ifndef _BRIDGE_STATE_H
#define _BRIDGE_STATE_H

namespace BridgeProblem {
	enum BridgeSide {
		LEFT,
		RIGHT
	};

	class BridgeState {
		public:
			BridgeSide getPersonSide(int i);
			void setPersonSide(int i, BridgeSide bs);

		private:
			BridgeSide peopleSides[6];
	};
}

#endif
