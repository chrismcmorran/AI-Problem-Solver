#include "TileAction.h"
#include "TileState.h"
#include <string>
#include <sstream>

using namespace TileProblem;

TileAction::TileAction(short x1, short y1, short x2, short y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

int TileAction::execute(const AI::State* state, AI::State** outState)
{
	// Assumes that state is always a TileState
	TileState* newState = new TileState(*static_cast<const TileState*>(state));

	// Swap tiles
	short t1 = newState->getTileValue(x1, y1);
	short t2 = newState->getTileValue(x2, y2);
	newState->setTileValue(x1, y1, t2);
	newState->setTileValue(x2, y2, t1);
	*outState = newState;

	// Cost = number of moves
	return 1;
}

static std::string tileString(short tileNum)
{
	// 0 -> blank tile
	std::ostringstream ss;
	if (tileNum == 0)
		ss << " ";
	else
		ss << tileNum;
	return ss.str();
}

std::string TileAction::describe(const AI::State* s)
{
	// Assumes that s is always a TileState
	const TileState* ts = static_cast<const TileState*>(s);

	short t1 = ts->getTileValue(x1, y1);
	short t2 = ts->getTileValue(x2, y2);

	std::ostringstream ss;
	ss << "Swap tile \'" << tileString(t1) << "\' with tile \'" << tileString(t2) << "\'.";
	return ss.str();
}
