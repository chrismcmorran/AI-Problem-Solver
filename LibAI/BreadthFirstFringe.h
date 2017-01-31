#ifndef _BREADTH_FIRST_FRINGE_CONTAINER_H
#define _BREADTH_FIRST_FRINGE_CONTAINER_H

#include <queue>
#include "Fringe.h"

namespace AI {
	/* Container for the fringe which facilitates breadth-first search (a queue) */
	template <typename T>
	class BreadthFirstFringe : public Fringe<T> {
		private:
			std::queue<T> container;

		public:
			virtual void push(const T& val)
			{
				container.push(val);
			}

			virtual void pop()
			{
				container.pop();
			}

			virtual T& front()
			{
				return container.front();
			}

			virtual bool empty()
			{
				return container.empty();
			}
	};
}

#endif