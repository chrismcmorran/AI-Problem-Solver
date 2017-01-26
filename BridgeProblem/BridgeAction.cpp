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

BridgeState* BridgeAction::execute(BridgeState& state)
{
	// Assumes at least one person will always be moved
	// Person index of -1 indicates "no person"
	BridgeState* newState = new BridgeState(state);
	newState->setPersonSide(person1, destSide);
	if (person2 != -1)
		newState->setPersonSide(person2, destSide);
	newState->setTorchSide(destSide);
	return newState;
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
