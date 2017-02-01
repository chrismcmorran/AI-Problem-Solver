#ifndef _TILE_ACTION_H
#define _TILE_ACTION_H

#include "../LibAI/Action.h"
#include "TileState.h"
#include <string>

namespace TileProblem {
	/* An action that can be performed on a state of the
	   tile problem (i.e., sliding/swapping tiles) */
	class TileAction : public AI::Action {
		public:
			TileAction(short row1, short col1, short row2, short col2);
			virtual int execute(const AI::State* inState, AI::State** outState);
			virtual std::string describe(const AI::State* s);

		private:
			short row1;
			short col1;
			short row2;
			short col2;
	};
}

#endif
