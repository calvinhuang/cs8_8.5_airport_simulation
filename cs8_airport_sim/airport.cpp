//
//  airport.cpp
//  cs8_airport_sim
//
//  Created by Calvin Huang on 2/26/18.
//

#include "airport.hpp"

void Airport::print_params()
{
	std::cout << "Seconds for one landing: " << landing_time << std::endl;
	std::cout << "Seconds for one takeoff: " << takeoff_time << std::endl;
	std::cout << "Probability of a plane arriving: " << landing_probability << std::endl;
	std::cout << "Probability of a plane taking off: " << takeoff_probability << std::endl;
	std::cout << "Total simulation time: " << total_time << std::endl;
}

void Airport::run_simulation()
{
	for (current_second = 1; current_second <= total_time; ++current_second)
	{ // One tick (1 s) of the simulation
		if (arrival.query()) {
			// New plane has arrived for landing
			arrival_times.push(current_second);
		}
		
		if (planes_in_hangar > 0 && takeoff.query()) {
			// Plane in hangar wants to take off
			planes_in_hangar--;
			takeoff_times.push(current_second);
		}
		if (!arrival_times.empty()) {
			// If there are planes waiting to land, try to land one
			int next_landing = -1;
			// Find one that hasn't run out of fuel yet
			do {
				next_landing = arrival_times.front();
				arrival_times.pop();
				if (current_second - next_landing > fuel_limit) {
					// Plane ran out of fuel while in holding pattern
					crashes++;
					next_landing = -1;
				}
			} while (next_landing < 0 && !arrival_times.empty());
			if (next_landing > 0 && !main_runway.is_busy()) {
				// Land a plane
				planes_in_hangar++;
				landing_wait_times.next_number(current_second - next_landing);
				main_runway.start_landing();
			}
		}
		if (!takeoff_times.empty() && !main_runway.is_busy()) {
			// Let a plane take off if runway is available
			unsigned int next_takeoff = takeoff_times.front();
			takeoff_times.pop();
			takeoff_wait_times.next_number(current_second - next_takeoff);
			main_runway.start_takeoff();
		}
		// Tick
		main_runway.one_second();
	}
	print_summary();
}

void Airport::print_summary()
{
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
