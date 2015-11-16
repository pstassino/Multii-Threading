// async example

// Calls fn at some point, returning without waiting for the execution of fn to complete.
// Futures are objects associated to a shared state, and are constructed
// by calling one of the following functions: async, promise::get_future, packaged_task::get_future

#include <iostream>       // std::cout
#include <future>         // std::async, std::future

// a non-optimized way of checking for prime numbers:
bool is_prime( int x ) {
	std::cout << "Calculating. Please, wait...\n";
	
	for( int i=2; i<x; ++i ) {
		if( x%i == 0)
			return false;
	}
	return true;
}

int main() {
	// call is_prime function asynchronously:
	std::future<bool> fut = std::async( is_prime, 313222313 );  

	std::cout << "Checking whether 313222313 is prime.\n";
	// ...						Parallel actions while the the is_prime function 

	bool ret = fut.get();      // waits for is_prime to return

	if( ret ) 
		std::cout << "It is prime!\n";
	else 
		std::cout << "It is not prime.\n";

	return 0;
}