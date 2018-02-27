//
//  queue.hpp
//  cs8_airport_sim
//
//  Created by Calvin Huang on 2/26/18.
//  Copyright © 2018 Calvin Huang. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include <cstdlib>


template <class T> class Queue
{
public:
	// TYPEDEFS and MEMBER CONSTANTS -- See Appendix E if this fails to compile. typedef std::size_t size_type;
	typedef T value_type;
	static const size_t CAPACITY = 100;
	// CONSTRUCTOR
	Queue() {};
	// MODIFICATION MEMBER FUNCTIONS
	void pop();
	void push(const T& entry);
	// CONSTANT MEMBER FUNCTIONS
	bool empty() const;
	T front() const;
	size_t size() const;
private:
	T data[CAPACITY]; // Circular array
	size_t first = 0;	// Index of item at the front of the queue
	size_t last = CAPACITY - 1;	// Index of item at the rear of the queue
	size_t count = 0;	// Total number of items in the queue
	// HELPER MEMBER FUNCTION
	size_t next_index(size_t i) const;
};

template<typename T>
bool Queue<T>::empty() const {
	return (count == 0);
}

template<typename T>
T Queue<T>::front() const {
	assert(!empty());
	return data[first];
}

template<typename T>
size_t Queue<T>::size() const {
	return count;
}

template<typename T>
size_t Queue<T>::next_index(size_t i) const {
	return (i + 1) % CAPACITY;
}

template<typename T>
void Queue<T>::pop() {
	assert(!empty());
	first = next_index(first);
	--count;
}

template<typename T>
void Queue<T>::push(const T& entry) {
	assert(size() < CAPACITY);
	last = next_index(last);
	data[last] = entry;
	++count;
}

#endif /* queue_hpp */
