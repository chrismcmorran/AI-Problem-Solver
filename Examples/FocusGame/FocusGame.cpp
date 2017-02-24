/*
   COMP 4106 - Assignment 2
   Matt Penny
*/

#include <cstdlib>
#include <ctime>
#include <climits>
#include <iostream>
#include "../../LibAI/Util.h"
#include "FocusAction.h"
#include "FocusState.h"
#include "FocusGame.h"

using namespace FocusGame;

Game::Game(unsigned int searchDepth) : AI::Game(searchDepth)
{
	int heurNum = AI::Util::getInt("Which heuristic function do you want to use?\n"
								   "1) Percentage of stacks controlled\n"
								   "2) NOT IMPLEMENTED\n", 1, 1);
	FocusState::setHeuristic((FocusHeuristic)heurNum);
	std::cout << std::endl;
}

AI::State* Game::genInitialState()
{
	return new FocusState;
}

bool Game::gameEnded(const AI::State* state) const
{
	// Assumes state is a FocusState
	const FocusState* fs = static_cast<const FocusState*>(state);
	return fs->gameEnded();
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
