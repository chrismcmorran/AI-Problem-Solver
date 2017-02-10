#include <list>
#include <queue>
#include <string>
#include <iostream>
#include "Problem.h"
#include "Action.h"
#include "BreadthFirstFringe.h"
#include "DepthFirstFringe.h"
#include "AStarFringe.h"

using namespace AI;

Problem::Problem(SearchType searchType)
{
	if (searchType == BREADTH_FIRST)
		fringe = new BreadthFirstFringe();
	else if (searchType == DEPTH_FIRST)
		fringe = new DepthFirstFringe();
	else
		fringe = new AStarFringe();

	this->searchType = searchType;
}

Problem::~Problem()
{
	delete fringe;
	delete goalState;
}

void Problem::expand(SearchNode* node)
{
	// Generate successor actions
	std::vector<Action*> actions;
	const State* state = node->getState();
	state->getActions(actions);

	for (unsigned int i = 0; i < actions.size(); ++i)
	{
		Action* action = actions.at(i);
		State* generatedState;
		int costFromRoot = node->getCostFromRoot() + action->execute(state, &generatedState);

		SearchNode* newNode = new SearchNode(generatedState, costFromRoot, action, node);
		fringe->push(newNode);
		node->incChildCount();

		if (searchType == A_STAR)
		{
			std::set<SearchNode*, NodeComp>::iterator it = closed.find(newNode);

			if (it != closed.end() && (*it)->getCostFromRoot() > newNode->getCostFromRoot())
			{
				/* Better path found. Instead of updating the existing node,
				   remove it from the closed set (if present) and add the new,
				   better-cost node to the fringe (this part is done above).
				   This effectively does the same thing but does not require
				   updating pointers (at the cost of some recomputation) */
				delete *it;
				closed.erase(it);
			}
		}
	}
}

static void outputSolution(SearchNode* node, std::ostream& out)
{
	std::list<SearchNode*> path;
	std::list<SearchNode*>::iterator it;

	// Traverse search tree to root to build path for solution
	while (node != NULL)
	{
		path.push_front(node);
		node = node->getParent();
	}

	// Output actions and states from the beginning of the problem to the end
	for (it = path.begin(); it != path.end(); ++it)
	{
		AI::Action* a = (*it)->getGeneratingAction();
		const AI::State* s = (*it)->getState();
		if (a != NULL)
			out << a->describe(s) << std::endl;
		out << s->describe() << std::endl;
		out << "Cumulative cost: " << (*it)->getCostFromRoot() << std::endl << std::endl;
	}
}

void Problem::cleanup()
{
	while (!fringe->empty())
	{
		SearchNode* node = fringe->front();
		fringe->pop();
		delete node;
	}
	for (std::set<SearchNode*, NodeComp>::iterator it = closed.begin(); it != closed.end(); ++it)
		delete *it;
}

void Problem::solve()
{
	fringe->push(new SearchNode(genInitialState()));
	goalState = genGoalState();

	while(!fringe->empty())
	{
		SearchNode* node = fringe->front();
		fringe->pop();

		// State in node has been seen before
		if (closed.find(node) != closed.end())
		{
			delete node;
			continue;
		}
		closed.insert(node);

		if (*node->getState() == *goalState)
		{
			// Solution found
			outputSolution(node, std::cout);
			cleanup();
			return;
		}
		else
		{
			// Generate successor nodes from the current node
			expand(node);
		}
	}
	std::cout << "No solution found" << std::endl;
	cleanup();
}
