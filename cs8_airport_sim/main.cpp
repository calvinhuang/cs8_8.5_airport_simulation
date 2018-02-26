//
//  main.cpp
//  cs8_airport_sim
//
//  Created by Calvin Huang on 2/26/18.
//  Copyright © 2018 Calvin Huang. All rights reserved.
//

#include <iostream>
#include <queue>
#include <cassert>
#include "washing.h"

class runway
{
public:
	// CONSTRUCTOR
	runway(unsigned int sl = 60, unsigned int st = 60) :
		seconds_for_landing(sl), seconds_for_takeoff(st), time_left(0) {}
	// MODIFICATION functions
	void one_second( ) {
		if (is_busy())
			--time_left;
	};
	void start_landing( )
	{
		assert(!is_busy());
		time_left = seconds_for_landing;
	};
	void start_takeoff( )
	{
		assert(!is_busy());
		time_left = seconds_for_takeoff;
	};
	// CONSTANT function
	bool is_busy( ) const { return (time_left > 0); }
private:
	unsigned int seconds_for_landing; // Seconds for a single landing
	unsigned int seconds_for_takeoff; // Seconds for a single takeoff
	unsigned int time_left;   // Seconds until washer no longer busy
};

void airport_simulate(unsigned int takeoff_time, double takeoff_probability, unsigned int landing_time, double landing_probability, unsigned int fuel_limit, unsigned int total_time) {
	// When each plane enters holding pattern
	std::queue<unsigned int> arrival_times;
	unsigned int planes_in_hangar = 0;
	// When each plane gets in line to takeoff
	std::queue<unsigned int> takeoff_times;
	main_savitch_8A::bool_source arrival(landing_probability);
	main_savitch_8A::bool_source takeoff(takeoff_probability);
	runway main_runway(landing_time, takeoff_time);
	main_savitch_8A::averager landing_wait_times, takeoff_wait_times;
	unsigned int current_second;
	unsigned int crashes = 0;
	
	std::cout << "Seconds for one landing: " << landing_time << std::endl;
	std::cout << "Seconds for one takeoff: " << takeoff_time << std::endl;
	std::cout << "Probability of a plane arriving: " << landing_probability << std::endl;
	std::cout << "Probability of a plane taking off: " << takeoff_probability << std::endl;
	std::cout << "Total simulation time: " << total_time << std::endl;
	std::cout << ". . . . . . . . . . . . . . . . . . . . . . . . . .\n";
	
	for (current_second = 1; current_second <= total_time; ++current_second)
	{ // One tick (1 s) of the simulation
		// Check whether a new plane has arrived for landing
		if (arrival.query()) {
			arrival_times.push(current_second);
		}
		if (planes_in_hangar > 0 && takeoff.query()) {
			planes_in_hangar--;
			takeoff_times.push(current_second);
		}
		if (!arrival_times.empty()) {
			int next_landing = -1;
			do {
				next_landing = arrival_times.front();
				arrival_times.pop();
				if (current_second - next_landing > fuel_limit) {
					crashes++;
					next_landing = -1;
				}
			} while (next_landing < 0 && !arrival_times.empty());
			if (next_landing > 0 && !main_runway.is_busy()) {
				planes_in_hangar++;
				landing_wait_times.next_number(current_second - next_landing);
				main_runway.start_landing();
			}
		}
		if (!takeoff_times.empty() && !main_runway.is_busy()) {
			unsigned int next_takeoff = takeoff_times.front();
			takeoff_times.pop();
			takeoff_wait_times.next_number(current_second - next_takeoff);
			main_runway.start_takeoff();
		}
		main_runway.one_second();
	}
	
	// Output simulation summary
	std::cout << landing_wait_times.how_many_numbers() << " landed\n";
	std::cout << takeoff_wait_times.how_many_numbers() << " took off\n";
	if (crashes > 0)
		std::cout << crashes << " planes crashed. :(\n";
	else
		std::cout << crashes << " planes crashed. :)\n";
	if (landing_wait_times.how_many_numbers() > 0)
		std::cout << "Average waiting time to land: " << landing_wait_times.average() << "\n";
	if (takeoff_wait_times.how_many_numbers() > 0)
		std::cout << "Average waiting time to takeoff: " << takeoff_wait_times.average() << "\n";
	std::cout << "Planes in landing queue: " << arrival_times.size() << "\n";
	std::cout << "Planes in takeoff queue: " << takeoff_times.size() << "\n";
}

int main(int argc, const char * argv[]) {
	// insert code here...
	unsigned int time_to_land = 5;
	unsigned int time_to_take_off = 15;
	double landing_probability = 0.10;
	double takeoff_probability = 0.8;
	unsigned int fuel_limit = 20;
	unsigned int simulation_time = 1440;
	
	airport_simulate(time_to_take_off, takeoff_probability, time_to_land, landing_probability, fuel_limit, simulation_time);
    return 0;
}

