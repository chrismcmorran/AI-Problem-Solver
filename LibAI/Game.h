#ifndef _GAME_H
#define _GAME_H

#include "State.h"

namespace AI {
	// A game to be played using AI
	class Game {
		public:
			Game(unsigned int searchDepth);
			virtual ~Game() {};
			virtual void play() const = 0;
			void nextMove(const State* currentState,
						  Action** outAction,
						  State** outState) const;

		private:
			unsigned int searchDepth;

			virtual bool gameEnded(const State* state) const = 0;
			int minimax(const State* s,
						unsigned int depth,
						Action** outAction,
						State** outState,
						int alpha,
						int beta) const;
	};
}

#endif
