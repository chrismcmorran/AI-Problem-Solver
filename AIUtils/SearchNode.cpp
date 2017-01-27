#include "SearchNode.h"

using namespace AI;

SearchNode::SearchNode(const State* state, Action* generatingAction, SearchNode* parent)
{
	this->state = state;
	this->generatingAction = generatingAction;
	this->parent = parent;
}

SearchNode::~SearchNode()
{
	delete state;
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