#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include "FocusAction.h"
#include "FocusState.h"

using namespace FocusGame;

FocusHeuristic FocusState::heuristic = CONTROLLED_STACKS;

void FocusState::setHeuristic(FocusHeuristic heuristic)
{
	FocusState::heuristic = heuristic;
}

FocusState::FocusState()
{
	// Initial state - pieces randomly placed in middle of board (not outer ring)
	short p1Pieces = 18, p2Pieces = 18;
	std::memset(board, 0, 64);
	for (short row = 1; row < 7; ++row)
	{
		for (short col = 1; col < 7; ++col)
		{
			if (p1Pieces > 0 && (p2Pieces == 0 || (std::rand() % 2)))
			{
				pushStackPiece(row, col, false);
				--p1Pieces;
			}
			else
			{
				pushStackPiece(row, col, true);
				--p2Pieces;
			}
		}
	}
	p1Captured = p2Captured = 0;
	p1Turn = true;
}

FocusState::FocusState(const FocusState &fs)
{
	std::memcpy(board, fs.board, 64);
	p1Captured = fs.p1Captured;
	p2Captured = fs.p2Captured;
	p1Turn = fs.p1Turn;
}

FocusStack FocusState::getStack(short row, short col) const
{
	unsigned char val = board[col + (row * 8)];
	return val;
}

void FocusState::setStack(short row, short col, FocusStack s)
{
	board[col + (row * 8)] = s;
}

short FocusState::getStackHeight(FocusStack s)
{
	return ((s >> 5) & 7);
}

void FocusState::pushStackPiece(short row, short col, bool p2)
{
	// Add a piece to the stack at (row, col) and increment its height
	unsigned char s = getStack(row, col);
	short height = getStackHeight(s) + 1;
	char overflowPiece = ((s >> 4) & 1);

	// Piece captured?
	if (height > 5)
	{
		if (p1Turn && overflowPiece == 1)
			++p1Captured;
		else if (!p1Turn && overflowPiece == 0)
			++p2Captured;
		height = 5;
	}

	s = (height << 5) | ((s & 0xF) << 1) | (p2 & 1);
	setStack(row, col, s);
}

void FocusState::removeStackPieces(short row, short col, short count)
{
	// Remove count pieces from the top of the stack at (row, col)
	unsigned char s = getStack(row, col);
	short height = getStackHeight(s) - count;
	if (height < 0)
		height = 0;
	if (count > 5)
		count = 5;
	s = ((height << 5) | ((s >> count) & 0x1F));
	setStack(row, col, s);
}

void FocusState::toggleTurn()
{
	p1Turn = !p1Turn;
}

bool FocusState::gameEnded() const
{
	/* The game ends when one player has no more valid
	   moves (i.e., no controlled stacks) or has captured
	   at least 8 enemy pieces */
	bool p1HasStacks = false, p2HasStacks = false;
	for (short i = 0; i < 64; ++i)
	{
		unsigned char s = board[i];
		if (getStackHeight(s) > 0)
		{
			if (board[i] & 1)
				p2HasStacks = true;
			else
				p1HasStacks = true;
		}
		if (p1HasStacks && p2HasStacks)
			break;
	}

	return p1Captured >= 8 || p2Captured >= 8 ||
		   !p1HasStacks || !p2HasStacks;
}

unsigned long FocusState::getStateCode() const
{
	// Don't need to compare this state for uniqueness. Just use its address
	return (unsigned long)this;
}

static void generateActions(std::vector<AI::Action*>& actions, short row, short col, short moveDist, bool splitting)
{
	// Keep moves within bounds
	int minRow = 0, minCol = 0, maxRow = 7, maxCol = 7;
	if (row == 0 || row == 7)
	{
		minCol = 2;
		maxCol = 5;
	}
	else if (row == 1 || row == 6)
	{
		minCol = 1;
		maxCol = 6;
	}
	if (col == 0 || col == 7)
	{
		minRow = 2;
		maxRow = 5;
	}
	else if (col == 1 || col == 6)
	{
		minRow = 1;
		maxRow = 6;
	}

	short startRow = std::max(minRow, row - moveDist);
	short endRow = std::min(maxRow, row + moveDist);
	short startCol = std::max(minCol, col - moveDist);
	short endCol = std::min(maxCol, col + moveDist);
	short i;

	// Stack can move up to moveDist spaces in either direction (within bounds)
	for (i = endCol; i >= startCol; --i)
		if (i != col)
			actions.push_back(new FocusAction(row, col, row, i, splitting));
	for (i = endRow; i >= startRow; --i)
		if (i != row)
			actions.push_back(new FocusAction(row, col, i, col, splitting));
}

void FocusState::getActions(std::vector<AI::Action*>& actions) const
{
	for (short row = 0; row < 8; ++row)
	{
		for (short col = 0; col < 8; ++col)
		{
			unsigned char stack = getStack(row, col);
			short height = getStackHeight(stack);

			// Stack controller = current player
			if (height > 0 && (stack & 1) != p1Turn)
			{
				// Stack can move up to height spaces in either direction
				generateActions(actions, row, col, height, false);

				// Full stacks also have the option to split the top 3 pieces
				if (height == 5)
					generateActions(actions, row, col, 3, true);
			}
		}
	}
}

void FocusState::describeRow(std::ostringstream& ss, short row, short startCol, short endCol) const
{
	for (short col = startCol; col < endCol; ++col)
	{
		unsigned char stack = getStack(row, col);
		if (getStackHeight(stack) == 0)
			ss << " ";
		else
			ss << ((stack & 1) ? "O" : "X");  // Top of stack = controlling player
	}
}

std::string FocusState::describe() const
{
	std::ostringstream ss;
	ss << "   ";
	for (short col = 0; col < 8; ++col)
		ss << col;
	ss << std::endl << "     ____" << std::endl;

	for (short row = 0; row < 8; ++row)
	{
		char leftCorner, rightCorner;
		if (row < 2)
		{
			leftCorner = '/';
			rightCorner = '\\';
		}
		else
		{
			leftCorner = '\\';
			rightCorner = '/';
		}

		// Draw the board
		ss << row << " ";
		if (row == 0 || row == 7)
		{
			ss << "  " << leftCorner;
			describeRow(ss, row, 2, 6);
			ss << rightCorner;
		}
		else if (row == 1 || row == 6)
		{
			ss << " " << leftCorner;
			describeRow(ss, row, 1, 7);
			ss << rightCorner;
		}
		else
		{
			ss << "|";
			describeRow(ss, row, 0, 8);
			ss << "|";
		}
		ss << std::endl;
	}
	ss << "Opponent pieces captured by X: " << p1Captured << std::endl;
	ss << "Opponent pieces captured by O: " << p2Captured << std::endl;

	// Player who went before wins
	if (gameEnded())
		ss << (p1Turn ? "O" : "X") << " wins!";
	return ss.str();
}

int FocusState::heuristicValue() const
{
	if (heuristic == CONTROLLED_STACKS)
	{
		// Heuristic 1: controlled stacks
		int controlledStacks = 0, opponentStacks = 0;
		for (short i = 0; i < 64; ++i)
		{
			unsigned char stack = board[i];
			if (getStackHeight(stack) > 0)
			{
				/* Utility is to be calculated for the player who just played,
				   not the one who is going next turn */
				if (p1Turn != (stack & 1))
					++controlledStacks;
				else
					++opponentStacks;
			}
		}
		return (controlledStacks - (opponentStacks * 10));
	}
	else
	{
		// Heuristic 2: captured pieces
		if (p1Turn)
			return ((p2Captured * 10) - p1Captured);
		else
			return ((p1Captured * 10) - p2Captured);
	}
}
