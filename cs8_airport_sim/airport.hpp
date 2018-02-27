//
//  airport.hpp
//  cs8_airport_sim
//
//  Created by Calvin Huang on 2/26/18.
//

#ifndef airport_hpp
#define airport_hpp

#include <iostream>
#include <cassert>
#include <queue>
#include "queue.hpp"
#include "probability_statistics.hpp"
#include "runway.hpp"

class Airport {
public:
	Airport(
			unsigned int to_tm,
			double to_prob,
			unsigned int l_tm,
			double l_prob,
			unsigned int f_lim,
			unsigned int tot_tm
			) :
		takeoff_time(to_tm),
		takeoff_probability(to_prob),
		landing_time(l_tm),
		landing_probability(l_prob),
		fuel_limit(f_lim),
		total_time(tot_tm),
		arrival(bool_source(to_prob)),
		takeoff(bool_source(l_prob)),
		main_runway(Runway(l_tm, to_tm))
	{
		print_params();
		std::cout << ". . . . . . . . . . . . . . . . . . . . . . . . . .\n";
	};
	unsigned int takeoff_time;
	double takeoff_probability;
	unsigned int landing_time;
	double landing_probability;
	unsigned int fuel_limit;
	unsigned int total_time;
	void print_params();
	void run_simulation();
	void print_summary();
private:
	// When each plane enters holding pattern
	Queue<unsigned int> arrival_times;
	unsigned int planes_in_hangar = 0;
	// When each plane gets in line to takeoff
	Queue<unsigned int> takeoff_times;
	bool_source arrival;
	bool_source takeoff;
	Runway main_runway;
	averager landing_wait_times;
	averager takeoff_wait_times;
	unsigned int current_second;
	unsigned int crashes = 0;
};

#endif /* airport_hpp */
