#include "TileAction.h"
#include "TileState.h"
#include <string>
#include <sstream>

using namespace TileProblem;

TileAction::TileAction(short row1, short col1, short row2, short col2)
{
	this->row1 = row1;
	this->col1 = col1;
	this->row2 = row2;
	this->col2 = col2;
}

int TileAction::execute(const AI::State* state, AI::State** outState)
{
	// Assumes that state is always a TileState
	TileState* newState = new TileState(*static_cast<const TileState*>(state));

	// Swap tiles
	short t1 = newState->getTileValue(row1, col1);
	short t2 = newState->getTileValue(row2, col2);
	newState->setTileValue(row1, col1, t2);
	newState->setTileValue(row2, col2, t1);
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

	short t1 = ts->getTileValue(row1, col1);
	short t2 = ts->getTileValue(row2, col2);

	std::ostringstream ss;
	ss << "Swap tile \'" << tileString(t1) << "\' with tile \'" << tileString(t2) << "\'.";
	return ss.str();
}
