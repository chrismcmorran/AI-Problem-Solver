#include "SearchNode.h"

using namespace AI;

SearchNode::SearchNode(const State* state, int cost, Action* generatingAction, SearchNode* parent)
{
	this->state = state;
	this->costFromRoot = cost;
	this->generatingAction = generatingAction;
	this->parent = parent;
	this->children = 0;
}

SearchNode::~SearchNode()
{
	delete generatingAction;
	delete state;
}

SearchNode* SearchNode::getParent() const
{
	return parent;
}

void SearchNode::setParent(SearchNode* parent)
{
	this->parent = parent;
}

const State* SearchNode::getState() const
{
	return state;
}

Action* SearchNode::getGeneratingAction() const
{
	return generatingAction;
}

void SearchNode::setGeneratingAction(Action* action)
{
	generatingAction = action;
}

int SearchNode::getCostFromRoot() const
{
	return costFromRoot;
}

void SearchNode::setCostFromRoot(int cost)
{
	costFromRoot = cost;
}

bool SearchNode::hasChildren() const
{
	return (children > 0);
}

void SearchNode::incChildCount()
{
	++children;
}

void SearchNode::decChildCount()
{
	--children;
}