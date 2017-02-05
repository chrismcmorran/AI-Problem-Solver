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
		allocatedNodes.insert(newNode);
		node->incChildCount();
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

void Problem::checkLeafNode(SearchNode* node)
{
	// Clean up nodes not on the solution path
	while (node != NULL && !node->hasChildren())
	{
		SearchNode* parent = node->getParent();
		if (parent != NULL)
			parent->decChildCount();
		delete node;
		allocatedNodes.erase(node);
		node = parent;
	}
}

void Problem::cleanup()
{
	while (!fringe->empty())
	{
		const State* s = fringe->front()->getState();
		fringe->pop();
		delete s;
	}
	for (std::set<SearchNode*>::iterator it = allocatedNodes.begin(); it != allocatedNodes.end(); ++it)
		delete *it;
	for (std::set<const State*, PointerComp<State>>::iterator it = seenStates.begin(); it != seenStates.end(); ++it)
		delete *it;
}

void Problem::solve()
{
	State* initialState = genInitialState();
	SearchNode* rootNode = new SearchNode(initialState);
	allocatedNodes.insert(rootNode);
	fringe->push(rootNode);
	goalState = genGoalState();

	while(!fringe->empty())
	{
		SearchNode* node = fringe->front();
		const AI::State* state = node->getState();
		fringe->pop();

		// Node has been seen before
		if (seenStates.find(state) != seenStates.end())
		{
			checkLeafNode(node);
			delete state;
			continue;
		}
		seenStates.insert(state);

		if (*state == *goalState)
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
			checkLeafNode(node);
		}
	}
	std::cout << "No solution found" << std::endl;
	cleanup();
}
