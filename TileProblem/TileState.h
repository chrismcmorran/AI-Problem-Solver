#ifndef _TILE_STATE_H
#define _TILE_STATE_H

#include "../LibAI/State.h"

namespace TileProblem {
	class TileAction;

	enum TileStateType {
		SHUFFLED,
		SOLVED
	};

	// A state of the tile problem
	class TileState : public AI::State {
		public:
			TileState(short boardWidth, short boardHeight, TileStateType stateType);
			TileState(const TileState &ts);
			virtual ~TileState();

			short getTileValue(short row, short col) const;
			void setTileValue(short row, short col, char v);

			virtual unsigned long getStateCode() const;
			virtual void getActions(std::vector<AI::Action*>& actions) const;
			virtual std::string describe() const;

		private:
			short* board;
			char boardWidth, boardHeight;
	};
}

#endif
