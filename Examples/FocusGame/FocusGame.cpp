/*
   COMP 4106 - Assignment 2
   Matt Penny
*/

#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include "../../LibAI/Action.h"
#include "../../LibAI/State.h"
#include "../../LibAI/Util.h"
#include "FocusState.h"
#include "FocusGame.h"

using namespace FocusGame;

Game::Game(unsigned int searchDepth) : AI::Game(searchDepth) {}

bool Game::gameEnded(const AI::State* state) const
{
	// Assumes state is a FocusState
	const FocusState* fs = static_cast<const FocusState*>(state);
	return fs->gameEnded();
}

void Game::play() const
{
	// 2 AI players, each using a different heuristic
	AI::State* currentState = new FocusState;  // Initial state
	AI::State* nextState = NULL;
	AI::Action* action = NULL;
	FocusHeuristic heuristic = CONTROLLED_STACKS;

	while (currentState != NULL)
	{
		std::cout << currentState->describe() << std::endl;
		nextMove(currentState, &action, &nextState);
		if (action != NULL)
			std::cout << action->describe(currentState) << std::endl;
		delete action;
		delete currentState;
		currentState = nextState;

		// Switch heuristic for next player
		heuristic = ((heuristic == CONTROLLED_STACKS) ? CAPTURED_PIECES : CONTROLLED_STACKS);
		FocusState::setHeuristic(heuristic);
	}
}

int main()
{
	unsigned int searchDepth = AI::Util::getInt("Look ahead by how many turns? ", 1, INT_MAX);
	std::cout << std::endl;
	Game game(searchDepth);
	std::srand((unsigned int)std::time(0));
	game.play();
	return 0;
}
