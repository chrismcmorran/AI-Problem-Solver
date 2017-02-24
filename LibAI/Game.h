#ifndef _GAME_H
#define _GAME_H

#include "State.h"

namespace AI {
	// A game to be played using AI
	class Game {
		public:
			Game(unsigned int searchDepth);
			virtual ~Game() {};
			void play();

		private:
			unsigned int searchDepth;

			virtual State* genInitialState() = 0;
			virtual bool gameEnded(const State* state) const = 0;
			int minimax(const State* s, unsigned int depth, Action** outAction, State** outState);
			bool player1;
	};
}

#endif
