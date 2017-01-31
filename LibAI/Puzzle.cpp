#include <list>
#include <queue>
#include <string>
#include <iostream>
#include "Puzzle.h"
#include "Action.h"
#include "BreadthFirstFringe.h"
#include "DepthFirstFringe.h"

using namespace AI;

Fringe<SearchNode*>* fringe;
std::set<const State*, PointerComp<State>> seenStates;

Puzzle::Puzzle(State* initialState, State* goalState, SearchType searchType)
{
	if (searchType == BREADTH_FIRST)
		fringe = new BreadthFirstFringe<SearchNode*>;
	else if (searchType == DEPTH_FIRST)
		fringe = new DepthFirstFringe<SearchNode*>;
	else
		fringe = NULL;

	fringe->push(new SearchNode(initialState));
	seenStates.insert(initialState);
	this->goalState = goalState;
}

Puzzle::~Puzzle()
{
	std::set<const State*, PointerComp<State>>::iterator it;
	for (it = seenStates.begin(); it != seenStates.end(); ++it)
		delete *it;
	delete goalState;

	while(!fringe->empty())
	{
		delete fringe->front();
		fringe->pop();
	}
	delete fringe;
}

void Puzzle::expand(SearchNode* node)
{
	// Generate successor actions
	std::vector<Action*> actions;
	const State* state = node->getState();
	state->getActions(actions);

	for (unsigned int i = 0; i < actions.size(); ++i)
	{
		// Add valid successor states to the fringe
		Action* action = actions.at(i);
		State* generatedState;
		int cost = action->execute(state, &generatedState);

		if (seenStates.find(generatedState) == seenStates.end())
		{
			// State has not been seen before
			fringe->push(new SearchNode(generatedState, node->getCostFromRoot() + cost, action, node));
			seenStates.insert(generatedState);
			node->incChildCount();
		}
		else
		{
			delete generatedState;
			delete action;
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
		if (a != NULL)
			out << a->describe() << std::endl;
		out << (*it)->getState()->describe() << std::endl;
		out << "Cumulative cost: " << (*it)->getCostFromRoot() << std::endl << std::endl;
		delete *it;
	}
}

void Puzzle::solve()
{
	while(!fringe->empty())
	{
		SearchNode* node = fringe->front();
		const AI::State* state = node->getState();
		fringe->pop();

		if (*state == *goalState)
		{
			// Solution found
			outputSolution(node, std::cout);
			return;
		}
		else
		{
			// Generate successor nodes from the current node
			expand(node);

			// Clean up nodes not on the solution path
			while (node != NULL && !node->hasChildren())
			{
				SearchNode* parent = node->getParent();
				if (parent != NULL)
					parent->decChildCount();
				delete node;
				node = parent;
			}
		}
	}
	std::cout << "No solution found" << std::endl;
}