#include "DepthFirstFringe.h"

using namespace AI;

void DepthFirstFringe::push(SearchNode* val)
{
	container.push(val);
}

void DepthFirstFringe::pop()
{
	container.pop();
}

SearchNode* DepthFirstFringe::front()
{
	return container.top();
}

bool DepthFirstFringe::empty()
{
	return container.empty();
}