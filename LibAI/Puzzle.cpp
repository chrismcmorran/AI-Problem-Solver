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
std::set<SearchNode*> allocatedNodes;

Puzzle::Puzzle(State* initialState, State* goalState, SearchType searchType)
{
	SearchNode* rootNode = new SearchNode(initialState);
	allocatedNodes.insert(rootNode);
	seenStates.insert(initialState);
	this->goalState = goalState;

	if (searchType == BREADTH_FIRST)
		fringe = new BreadthFirstFringe<SearchNode*>;
	else if (searchType == DEPTH_FIRST)
		fringe = new DepthFirstFringe<SearchNode*>;
	else
		fringe = NULL;

	fringe->push(rootNode);
}

Puzzle::~Puzzle()
{
	std::set<const State*, PointerComp<State>>::iterator stateIt;
	std::set<SearchNode*>::iterator nodeIt;
	for (stateIt = seenStates.begin(); stateIt != seenStates.end(); ++stateIt)
		delete *stateIt;
	for (nodeIt = allocatedNodes.begin(); nodeIt != allocatedNodes.end(); ++nodeIt)
		delete *nodeIt;
	delete fringe;
	delete goalState;
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
			SearchNode* newNode = new SearchNode(generatedState, node->getCostFromRoot() + cost, action, node);
			fringe->push(newNode);
			allocatedNodes.insert(newNode);
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
		const AI::State* s = (*it)->getState();
		if (a != NULL)
			out << a->describe(s) << std::endl;
		out << s->describe() << std::endl;
		out << "Cumulative cost: " << (*it)->getCostFromRoot() << std::endl << std::endl;
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
				allocatedNodes.erase(node);
				node = parent;
			}
		}
	}
	std::cout << "No solution found" << std::endl;
}
