#include "BridgeState.h"

using namespace BridgeProblem;

BridgeSide BridgeState::getPersonSide(int i)
{
	return peopleSides[i];
}

void BridgeState::setPersonSide(int i, BridgeSide bs)
{
	peopleSides[i] = bs;
}