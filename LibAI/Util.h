#ifndef _UTIL_H
#define _UTIL_H

#include <string>

namespace AI {
	// Utility functions
	class Util {
		public:
			static int getInt(std::string prompt, int min=0, int max=0);
	};
}

#endif
