#ifndef _FOCUS_STATE_H
#define _FOCUS_STATE_H

#include <vector>
#include "../../LibAI/State.h"

namespace FocusGame {
	class FocusAction;

	/* The bits in each 8-bit integer in the board represent
	   a stack of pieces. A 0 bit indicates player 1 and a 1 bit
	   indicates player 2. Pieces are ordered from LSB to MSB.

	   Since only a maximum of 5 pieces are allowed in a stack,
	   the upper 3 bits store its height */
	typedef unsigned char FocusStack;

	enum FocusHeuristic {
		CONTROL_PERCENT = 1
	};

	// A state of the Focus game
	class FocusState: public AI::State {
		public:
			FocusState();
			FocusState(const FocusState &fs);

			FocusStack getStack(short row, short col) const;
			void setStack(short row, short col, FocusStack s);
			static short getStackHeight(FocusStack s);
			void pushStackPiece(short row, short col, bool p2);
			void removeStackPieces(short row, short col, short count);
			void toggleTurn();

			unsigned long getStateCode() const;
			virtual void getActions(std::vector<AI::Action*>& actions) const;
			virtual std::string describe() const;
			virtual int heuristicValue() const;
			virtual bool gameEnded() const;

			static void setHeuristic(FocusHeuristic heuristic);

		private:
			FocusStack board[64];  // 8x8
			short p1Captured, p2Captured;
			bool p1Turn;

			void describeRow(std::ostringstream& ss, short row, short startCol, short endCol) const;
			static FocusHeuristic heuristic;
	};
}

#endif
