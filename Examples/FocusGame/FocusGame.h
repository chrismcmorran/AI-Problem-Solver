#ifndef _FOCUS_GAME_H
#define _FOCUS_GAME_H

#include "../../LibAI/Game.h"
#include "../../LibAI/State.h"

namespace FocusGame {
	/* Focus/Domination:

	   A board game played on a grid. Pieces can be stacked on top of each other.
	   A player is said to control a stack if one of their pieces is topmost. On
	   a player's turn, they can move a stack they control vertically or horizontally
	   any number of grid cells up to the number of pieces being moved. When a stack is
	   moved on top of another and the new height is greater than 5, the lower pieces
	   are captured by the player who made the move. Each player starts with 18 pieces
	   randomly placed in the inner 6x6 square of the board. The game ends when one player,
	   the loser, has no more valid moves (i.e., the other player controls all of the stacks).

	   Note that this game is modified from the original 1964 version: players may choose
	   to move only the top 3 pieces of a stack of height 5 on their turn, the "self capture"
	   rule is not implemented, and the game can end early if one player captures 8 or more
	   of the opponent's pieces. See https://en.wikipedia.org/wiki/Focus_(board_game) for the
	   original rules. */
	class Game : public AI::Game {
		public:
			Game(unsigned int searchDepth);
			void play() const;

		private:
			virtual bool gameEnded(const AI::State* state) const;
			unsigned int searchDepth;
	};
}

#endif
