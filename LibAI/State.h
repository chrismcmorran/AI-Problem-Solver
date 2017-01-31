#ifndef _STATE_H
#define _STATE_H

#include <string>
#include <vector>

namespace AI {
	class Action;
	class State {
		// A given state of the puzzle
		public:
			virtual unsigned long getStateCode() const = 0;
			virtual void getActions(std::vector<Action*>& actions) const = 0;
			virtual std::string describe() const = 0;
			virtual ~State() {};

			bool operator<(const State& other) const;
			bool operator>(const State& other) const;
			bool operator<=(const State& other) const;
			bool operator>=(const State& other) const;
			bool operator==(const State& other) const;
			bool operator!=(const State& other) const;
	};
}

#endif
