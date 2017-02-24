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

int Game::minimax(const State* s, unsigned int depth, Action** outAction, State** outState, int alpha, int beta)
{
	if (depth == 0 || gameEnded(s))
		return s->heuristicValue();
	else
	{
		const int& (*comp)(const int&, const int&);
		int bestUtility;
		int* pruneVal;
		std::vector<Action*> actions;
		s->getActions(actions);

		if (depth % 2)
		{
			// Minimizing
			comp = std::min;
			bestUtility = INT_MAX;
			pruneVal = &beta;
		}
		else
		{
			comp = std::max;
			bestUtility = INT_MIN;
			pruneVal = &alpha;
		}

		// Generate and evaluate possible actions
		for (unsigned int i = 0; i < actions.size(); ++i)
		{
			int utility;
			State* generatedState;
			Action* action = actions.at(i);

			// A better path exists at another node - stop evaluating children
			if (i > 0 && beta <= alpha)
			{
				delete action;
				continue;
			}

			action->execute(s, &generatedState);
			utility = minimax(generatedState, depth - 1, outAction, outState, alpha, beta);
			*pruneVal = comp(*pruneVal, utility);
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
