#include <algorithm>
#include <iostream>
#include <climits>
#include "Action.h"
#include "Game.h"

using namespace AI;

Game::Game(unsigned int searchDepth)
{
	this->searchDepth = searchDepth;
	player1 = true;
}

int Game::minimax(const State* s, unsigned int depth, Action** outAction, State** outState)
{
	if (depth == 0 || gameEnded(s))
		return s->heuristicValue();
	else
	{
		const int& (*comp)(const int&, const int&);
		int bestUtility;
		std::vector<Action*> actions;
		s->getActions(actions);

		if (depth % 2)
		{
			comp = std::min;
			bestUtility = INT_MAX;
		}
		else
		{
			comp = std::max;
			bestUtility = INT_MIN;
		}

		// Generate and evaluate possible actions
		for (unsigned int i = 0; i < actions.size(); ++i)
		{
			int utility;
			State* generatedState;
			Action* action = actions.at(i);
			action->execute(s, &generatedState);

			utility = minimax(generatedState, depth - 1, outAction, outState);
			bestUtility = comp(utility, bestUtility);

			if (utility == bestUtility && depth == searchDepth)
			{
				// Update best move
				delete *outAction;
				delete *outState;
				*outAction = action;
				*outState = generatedState;
			}
			else
			{
				delete action;
				delete generatedState;
			}
		}
		return bestUtility;
	}
}

void Game::play()
{
	State* currentState = NULL;
	State* nextState = genInitialState();
	Action* nextAction = NULL;

	while (currentState == NULL || !gameEnded(currentState))
	{
		if (nextAction != NULL)
			std::cout << nextAction->describe(currentState) << std::endl;

		delete nextAction;
		delete currentState;
		currentState = nextState;
		nextAction = NULL;
		nextState = NULL;

		std::cout << currentState->describe() << std::endl;	

		// Play next move
		minimax(currentState, searchDepth, &nextAction, &nextState);
		player1 = !player1;
	}

	delete currentState;
	delete nextState;
	delete nextAction;
}
