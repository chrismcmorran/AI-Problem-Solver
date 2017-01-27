#include <sstream>
#include "BridgeAction.h"
#include "BridgeState.h"

using namespace BridgeProblem;

BridgeState::BridgeState(BridgeSide startingSide)
{
	// Initial state
	torchSide = startingSide;
	for (int i = 0; i < 6; ++i)
		peopleSides[i] = startingSide;
}

BridgeState::BridgeState(const BridgeState &bs)
{
	// Assumes peopleSides arrays are equal in length
	memcpy(peopleSides, bs.peopleSides, sizeof(peopleSides));
}

BridgeSide BridgeState::getPersonSide(int i) const
{
	return peopleSides[i];
}

void BridgeState::setPersonSide(int i, BridgeSide bs)
{
	peopleSides[i] = bs;
}

BridgeSide BridgeState::getTorchSide() const
{
	return torchSide;
}

void BridgeState::setTorchSide(BridgeSide bs)
{
	torchSide = bs;
}

int BridgeState::getStateCode() const
{
	// TODO: will this scale?
	int s = 0;
	for (int i = 0; i < 6; ++i)
	{
		if (getPersonSide(i) == RIGHT)
			s |= (1 << (i+1));
	}
	if (torchSide == RIGHT)
		s |= 1;
	return s;
}

static void genMoves(std::vector<AI::Action*>& actions, std::vector<int>& people, BridgeSide dest, int start, int p2)
{
	// Generate all moves using a fixed person2 (i.e., all pairs including p2)
	for (unsigned int i = start; i < people.size(); ++i)
	{
		int p1 = people.at(i);
		actions.push_back(new BridgeAction(dest, p1, p2));
	}
}

void BridgeState::getActions(std::vector<AI::Action*>& actions) const
{
	BridgeSide dest = (torchSide == LEFT) ? RIGHT : LEFT;
	std::vector<int> people;
	unsigned int i;

	// Which people can be moved (who's on the same side as the torch)?
	for (i = 0; i < 6; ++i)
	{
		if (peopleSides[i] == torchSide)
			people.push_back(i);
	}

	// Generate all possible moves that can be made from the current state
	genMoves(actions, people, dest, 0, -1);
	for (i = 0; i < people.size(); ++i)
	{
		int p2 = people.at(i);
		genMoves(actions, people, dest, i+1, p2);
	}
}

std::string BridgeState::describe() const
{
	// Draws the current state
	std::ostringstream ss;
	std::vector<int> rightPeople;
	unsigned int i;
	for (i = 0; i < 6; ++i)
	{
		if (peopleSides[i] == LEFT)
			ss << i << " ";
		else
		{
			ss << "  ";
			rightPeople.push_back(i);
		}
	}

	if (torchSide == LEFT)
		ss << "* ";
	else
		ss << "  ";

	ss << " =================================== ";

	if (torchSide == RIGHT)
		ss << " * ";
	else
		ss << " ";

	for (i = 0; i < rightPeople.size(); ++i)
		ss << rightPeople.at(i) << " ";
	return ss.str();
}