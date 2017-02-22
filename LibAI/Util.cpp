#include "Util.h"
#include <iostream>
#include <sstream>

using namespace AI;

int Util::getInt(std::string prompt, int min, int max)
{
	// Get int from user and validate input
	std::string input;
	int i;

	while (true)
	{
		std::cout << prompt;
		std::cin >> input;
		std::stringstream ss(input);
		ss >> i;

		if (ss.fail() || i < min || i > max)
			std::cout << "Invalid input. ";
		else
			return i;
	}
}
