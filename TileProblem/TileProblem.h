#ifndef _TILE_PROBLEM_H
#define _TILE_PROBLEM_H

#include "../LibAI/Problem.h"
#include "../LibAI/State.h"

namespace TileProblem {
	/* The tile problem:

	   An mxn grid contains tiles with the numbers 1 through (mxn)-1 on them.
	   Initially these tiles are in a random order. One space is left blank. The
	   goal is to arrange the tiles in the correct order.

	   -Any tile that is adjacent or diagonal to the blank space can slide into it
	   -Two non-blank tiles can be swapped as per the chess "horse move" */
	class Problem : public AI::Problem {
		public:
			Problem(AI::SearchType searchType);

		private:
			short width, height;

			virtual AI::State* genInitialState();
			virtual AI::State* genGoalState();
	};
}

#endif
