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
}

SearchNode* SearchNode::getParent()
{
	return parent;
}

const State* SearchNode::getState()
{
	return state;
}

Action* SearchNode::getGeneratingAction()
{
	return generatingAction;
}

int SearchNode::getCostFromRoot()
{
	return costFromRoot;
}

bool SearchNode::hasChildren()
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