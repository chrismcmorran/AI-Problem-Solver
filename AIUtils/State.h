#ifndef _STATE_H
#define _STATE_H

#include <vector>

namespace AI {
	class Action;
	class State {
		// A given state of the puzzle
		public:
			virtual int getStateCode() const = 0;
			virtual void getActions(std::vector<Action*>& actions) const = 0;
			virtual std::string describe() const = 0;

			bool operator<(const State& other) const;
			bool operator>(const State& other) const;
			bool operator<=(const State& other) const;
			bool operator>=(const State& other) const;
			bool operator==(const State& other) const;
			bool operator!=(const State& other) const;
	};
}

#endif
