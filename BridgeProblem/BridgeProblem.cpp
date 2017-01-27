#include "../AIUtils/Puzzle.h"
#include "BridgeState.h"

using namespace BridgeProblem;

/* The bridge problem:

   A number of people must move over a narrow bridge at night. The bridge can
   only hold two people at a time and a torch has to be used to cross the bridge.
   Each person takes a certain amount of time to cross the bridge. When two persons
   are crossing the bridge together, they both move at the pace dictated by the
   slower person. The task is get the group across the bridge in the minimum time. */

int main()
{
	BridgeState* initial = new BridgeState(LEFT);
	BridgeState* goal = new BridgeState(RIGHT);
	AI::Puzzle bridgePuzzle(initial, goal, AI::DEPTH_FIRST);
	bridgePuzzle.solve();
	//delete initial;
	//delete goal;

	return 0;
}