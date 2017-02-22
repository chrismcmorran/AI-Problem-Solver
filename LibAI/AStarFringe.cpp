#include <queue>
#include "AStarFringe.h"

using namespace AI;

void AStarFringe::push(SearchNode* val)
{
	container.push(val);
}

void AStarFringe::pop()
{
	container.pop();
}

SearchNode* AStarFringe::front()
{
	return container.top();
}

bool AStarFringe::empty()
{
	return container.empty();
}
