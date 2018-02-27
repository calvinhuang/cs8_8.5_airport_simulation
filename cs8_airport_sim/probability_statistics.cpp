//
//  probility_statistics.cpp
//  cs8_airport_sim
//
//  Pulled from Michael Main, Walter Savitch's
//	Data Structures and Other Objects Using C++ (4th ed.)
//

#include "probability_statistics.hpp"

bool_source::bool_source(double p)
{
	assert(p >= 0);
	assert(p <= 1);
	probability = p;
}

bool bool_source::query( ) const
{
	return (rand() < probability * RAND_MAX);
}

averager::averager( )
{
	count = 0;
	sum = 0;
}

void averager::next_number(double value)
{
	++count;
	sum += value;
}

double averager::average() const
{
	assert(how_many_numbers() > 0);
	return sum/count;
}
