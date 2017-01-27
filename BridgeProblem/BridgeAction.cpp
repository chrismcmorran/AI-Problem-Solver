#include "BridgeAction.h"
#include "BridgeState.h"
#include <string>
#include <sstream>

using namespace BridgeProblem;

BridgeAction::BridgeAction(BridgeSide dest, int p1, int p2)
{
	destSide = dest;
	person1 = p1;
	person2 = p2;
}

int BridgeAction::execute(const AI::State* state, AI::State** outState)
{
	// Assumes at least one person will always be moved, and that state is always a BridgeState
	// Person index of -1 indicates "no person"
	BridgeState* newState = new BridgeState(*static_cast<const BridgeState*>(state));
	int cost = newState->getPersonTime(person1);
	newState->setPersonSide(person1, destSide);
	if (person2 != -1)
	{
		int p2Time = newState->getPersonTime(person2);
		newState->setPersonSide(person2, destSide);
		if (p2Time > cost)
			cost = p2Time;
	}
	newState->setTorchSide(destSide);
	*outState = newState;

	// Cost = slowest time between the people moved
	return cost;
}

std::string BridgeAction::describe()
{
	// Assumes at least one person will always be moved
	std::ostringstream ss;
	ss << "Move person " << person1;
	if (person2 != -1)
		ss << " and person " << person2;
	ss << " to the " << ((destSide == LEFT) ? "left" : "right") << " side of the bridge.";
	return ss.str();
}
