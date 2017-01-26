#include <string>
#include <iostream>
#include <set>

#include "BridgeState.h"

using namespace BridgeProblem;

int main()
{
	// Value is the bridge crossing speed of the person
	int people[6] = {1,2,3,4,5,6};
	std::set<BridgeState, bool (*)(const BridgeState& a, const BridgeState& b)> seenStates(&BridgeState::compare);

	BridgeState initialState;
	seenStates.insert(initialState);

	std::vector<AIUtils::Action*> actions;
	initialState.getActions(actions);

	// Cleanup
	for (unsigned int i = 0; i < actions.size(); ++i)
	{
		std::cout << actions.at(i)->describe() << std::endl;
		delete actions.at(i);
	}

	return 0;
}