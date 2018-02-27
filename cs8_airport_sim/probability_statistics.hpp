//
//  probility_statistics.hpp
//  cs8_airport_sim
//
//  Pulled from Michael Main, Walter Savitch's
//	Data Structures and Other Objects Using C++ (4th ed.)
//

#ifndef probility_statistics_hpp
#define probility_statistics_hpp

#include <cstdlib>
#include <cassert>


class bool_source
{
public:
	// CONSTRUCTOR
	bool_source(double p = 0.5);
	// CONSTANT function
	bool query( ) const;
private:
	double probability; // Probability of query( ) returning true
};

class averager
{
public:
	// CONSTRUCTOR
	averager( );
	// MODIFICATION function
	void next_number(double value);
	// CONSTANT functions
	std::size_t how_many_numbers( ) const { return count; }
	double average( ) const;
private:
	std::size_t count; // How many numbers have been given to the averager
	double sum;   // Sum of all the numbers given to the averager
};

#endif /* probility_statistics_hpp */
