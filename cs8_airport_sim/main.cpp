//
//  main.cpp
//  cs8_airport_sim
//
//  Created by Calvin Huang on 2/26/18.
//

#include "airport.hpp"

int main(int argc, const char * argv[]) {
	// insert code here...
	unsigned int time_to_land = 5;
	unsigned int time_to_take_off = 15;
	double landing_probability = 0.10;
	double takeoff_probability = 0.8;
	unsigned int fuel_limit = 20;
	unsigned int simulation_time = 1440;
	
	Airport airport(
		time_to_take_off, takeoff_probability, time_to_land, landing_probability, fuel_limit, simulation_time
		);
	airport.run_simulation();
	
    return 0;
}

