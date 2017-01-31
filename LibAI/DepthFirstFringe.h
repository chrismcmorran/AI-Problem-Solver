#ifndef _DEPTH_FIRST_FRINGE_CONTAINER_H
#define _DEPTH_FIRST_FRINGE_CONTAINER_H

#include <stack>
#include "Fringe.h"

namespace AI {
	/* Container for the fringe which facilitates depth-first search (a stack) */
	template <typename T>
	class DepthFirstFringe : public Fringe<T> {
		private:
			std::stack<T> container;

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
				return container.top();
			}

			virtual bool empty()
			{
				return container.empty();
			}
	};
}

#endif