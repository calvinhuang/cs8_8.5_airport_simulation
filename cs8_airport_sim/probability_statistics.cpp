//
//  probility_statistics.cpp
//  cs8_airport_sim
//
//  Created by Calvin Huang on 2/26/18.
//  Copyright © 2018 Calvin Huang. All rights reserved.
//

#include "probability_statistics.hpp"

bool_source::bool_source(double p)
// Library facilities used: cassert
{
	assert(p >= 0);
	assert(p <= 1);
	probability = p;
}

bool bool_source::query( ) const
// Library facilities used: cstdlib
{
	return (rand( ) < probability * RAND_MAX);
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

double averager::average( ) const
// Library facilities used: cassert
{
	assert(how_many_numbers( ) > 0);
	return sum/count;
}
