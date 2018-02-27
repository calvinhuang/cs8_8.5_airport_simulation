//
//  runway.h
//  cs8_airport_sim
//
//  Created by Calvin Huang on 2/26/18.
//  Copyright © 2018 Calvin Huang. All rights reserved.
//

#ifndef runway_h
#define runway_h

class Runway
{
public:
	// CONSTRUCTOR
	Runway(unsigned int sl = 60, unsigned int st = 60) :
	seconds_for_landing(sl), seconds_for_takeoff(st), time_left(0) {}
	// MODIFICATION functions
	void one_second();
	void start_landing();
	void start_takeoff();
	// CONSTANT function
	bool is_busy( ) const;
private:
	unsigned int seconds_for_landing; // Seconds for a single landing
	unsigned int seconds_for_takeoff; // Seconds for a single takeoff
	unsigned int time_left;   // Seconds until washer no longer busy
};

#endif /* runway_h */
