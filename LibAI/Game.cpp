#include <algorithm>
#include <iostream>
#include <climits>
#include "Action.h"
#include "Game.h"

using namespace AI;

Game::Game(unsigned int searchDepth)
{
	this->searchDepth = searchDepth;
}

int Game::minimax(const State* s,
				  unsigned int depth,
				  Action** outAction,
				  State** outState,
				  int alpha,
				  int beta) const
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

		if ((searchDepth - depth) % 2)
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

			// If a better path exists at another node, stop evaluating children
			if (i == 0 || beta > alpha)
			{
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
			else
				delete action;
		}
		return bestUtility;
	}
}

void Game::nextMove(const State* currentState,
					Action** outAction,
					State** outState) const
{
	*outAction = NULL;
	*outState = NULL;

	// Generate the next move using minimax
	if (!gameEnded(currentState))
		minimax(currentState, searchDepth, outAction, outState, INT_MIN, INT_MAX);
}
