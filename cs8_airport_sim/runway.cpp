//
//  runway.cpp
//  cs8_airport_sim
//
//  Created by Calvin Huang on 2/26/18.
//

#include <cassert>
#include "runway.hpp"

void Runway::one_second( ) {
	if (is_busy())
		--time_left;
};

void Runway::start_landing( )
{
	assert(!is_busy());
	time_left = seconds_for_landing;
};

void Runway::start_takeoff( )
{
	assert(!is_busy());
	time_left = seconds_for_takeoff;
};

bool Runway::is_busy( ) const {
	return (time_left > 0);
}
