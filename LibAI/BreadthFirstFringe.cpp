#include "BreadthFirstFringe.h"

using namespace AI;

void BreadthFirstFringe::push(SearchNode* val)
{
	container.push(val);
}

void BreadthFirstFringe::pop()
{
	container.pop();
}

SearchNode* BreadthFirstFringe::front()
{
	return container.front();
}

bool BreadthFirstFringe::empty()
{
	return container.empty();
}
