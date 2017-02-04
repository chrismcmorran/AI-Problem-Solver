#ifndef _TILE_STATE_H
#define _TILE_STATE_H

#include "../LibAI/State.h"

namespace TileProblem {
	class TileAction;

	enum TileHeuristic {
		MISPLACED_TILES = 1,
		MANHATTAN_DISTANCE,
		AVERAGE
	};

	// A state of the tile problem
	class TileState : public AI::State {
		public:
			TileState();
			TileState(const TileState &ts);
			virtual ~TileState();

			short getTileValue(short row, short col) const;
			void setTileValue(short row, short col, short v);

			virtual unsigned long getStateCode() const;
			virtual void getActions(std::vector<AI::Action*>& actions) const;
			virtual std::string describe() const;
			virtual int estimateGoalDist() const;

			static void setBoardDimensions(short width, short height);
			static short getBoardWidth();
			static short getBoardHeight();
			static void setHeuristic(TileHeuristic heuristic);

		private:
			short* board;
			static short boardWidth, boardHeight;
			static TileHeuristic heuristic;
	};
}

#endif
