#ifndef _FOCUS_ACTION_H
#define _FOCUS_ACTION_H

#include "../../LibAI/Action.h"
#include "FocusState.h"
#include <string>

namespace FocusGame {
	/* An action that can be performed on a state of the
	   focus game (i.e., moving pieces) */
	class FocusAction : public AI::Action {
		public:
			FocusAction(short row1, short col1, short row2, short col2, bool splitting);
			virtual int execute(const AI::State* inState, AI::State** outState);
			virtual std::string describe(const AI::State* s);

		private:
			short row1;
			short col1;
			short row2;
			short col2;
			bool splitting;
	};
}

#endif
