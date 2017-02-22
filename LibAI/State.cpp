#include "State.h"

using namespace AI;

bool State::operator<(const State& other) const
{
	return getStateCode() < other.getStateCode();
}

bool State::operator>(const State& other) const
{
	return getStateCode() > other.getStateCode();
}

bool State::operator<=(const State& other) const
{
	return !operator>(other);
}

bool State::operator>=(const State& other) const
{
	return !operator<(other);
}

bool State::operator==(const State& other) const
{
	return !operator<(other) && !operator>(other);
}

bool State::operator!=(const State& other) const
{
	return !operator==(other);
}
