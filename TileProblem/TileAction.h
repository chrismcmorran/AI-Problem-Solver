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
			TileAction(short x1, short y1, short x2, short y2);
			virtual int execute(const AI::State* inState, AI::State** outState);
			virtual std::string describe(const AI::State* s);

		private:
			short x1;
			short y1;
			short x2;
			short y2;
	};
}

#endif
