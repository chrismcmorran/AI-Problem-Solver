#include <string>
#include <sstream>
#include "FocusAction.h"
#include "FocusState.h"

using namespace FocusGame;

FocusAction::FocusAction(short row1, short col1, short row2, short col2, bool splitting)
{
	this->row1 = row1;
	this->col1 = col1;
	this->row2 = row2;
	this->col2 = col2;
	this->splitting = splitting;
}

int FocusAction::execute(const AI::State* state, AI::State** outState)
{
	// Assumes that state is always a FocusFocus
	FocusState* newState = new FocusState(*static_cast<const FocusState*>(state));

	// Place stack from start position onto that at dest position
	FocusStack stack = newState->getStack(row1, col1);
	int height = (splitting ? 3 : FocusState::getStackHeight(stack));

	newState->removeStackPieces(row1, col1, height);

	while (--height >= 0)
		newState->pushStackPiece(row2, col2, ((stack >> height) & 1));
	newState->toggleTurn();
	*outState = newState;

	// 1 move
	return 1;
}

std::string FocusAction::describe(const AI::State* s)
{
	// Assumes that s is always a FocusState
	const FocusState* fs = static_cast<const FocusState*>(s);
	FocusStack stack1 = fs->getStack(row1, col1);
	FocusStack stack2 = fs->getStack(row2, col2);
	std::ostringstream ss;

	ss << ((stack1 & 1) ? "O" : "X") << " moves ";
	if (splitting)
		ss << "the top 3 pieces of ";
	else
		ss << FocusState::getStackHeight(stack1) << "-piece ";
	ss << "stack at (" << row1 << "," << col1 << ") to ";

	if (FocusState::getStackHeight(stack2) > 0)
		ss << FocusState::getStackHeight(stack2) << "-piece stack at ";
	ss << "(" << row2 << "," << col2 << ")";

	return ss.str();
}
