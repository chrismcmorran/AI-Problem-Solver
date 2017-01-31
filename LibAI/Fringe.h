#ifndef _FRINGE_H
#define _FRINGE_H

namespace AI {
	/* Container for the fringe. Implementation will affect
	   state space search behavior */
	template <typename T>
	class Fringe {
		public:
			virtual void push(const T& val) = 0;
			virtual void pop() = 0;
			virtual T& front() = 0;
			virtual bool empty() = 0;
			virtual ~Fringe() {};
	};
}

#endif