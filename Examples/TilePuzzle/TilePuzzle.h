#ifndef _TILE_PUZZLE_H
#define _TILE_PUZZLE_H

#include "../../LibAI/Puzzle.h"
#include "../../LibAI/State.h"

namespace TilePuzzle {
	/* The tile puzzle:

	   An mxn grid contains tiles with the numbers 1 through (mxn)-1 on them.
	   Initially these tiles are in a random order. One space is left blank. The
	   goal is to arrange the tiles in the correct order.

	   -Any tile that is adjacent or diagonal to the blank space can slide into it
	   -Two non-blank tiles can be swapped as per the chess "horse move" */
	class Puzzle : public AI::Puzzle {
		public:
			Puzzle(AI::SearchType searchType);

		private:
			virtual AI::State* genInitialState() const;
			virtual AI::State* genGoalState() const;
	};
}

#endif
