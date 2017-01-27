#include "SearchNode.h"

using namespace AI;

SearchNode::SearchNode(const State* state, int cost, Action* generatingAction, SearchNode* parent)
{
	this->state = state;
	this->costFromRoot = cost;
	this->generatingAction = generatingAction;
	this->parent = parent;
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
