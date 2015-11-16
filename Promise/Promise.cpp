// promise example
// A promise is a provider that can store a value of type T 
// to be retrieved by a future object offering a synchronization point.
// Futures are objects associated to a shared state, and are constructed 
// by calling one of the following functions: async, promise::get_future, packaged_task::get_future

#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
#include <string>

void print_str( std::future<std::string>& fut ) {
	std::string  x = fut.get();
	std::cout << "Value: " << x << '\n';
}

int main() {
	std::promise<std::string> prom;                      // Create promise in the main thread
	std::future<std::string> fut = prom.get_future();    // Engage the promise with future

	std::thread th( print_str, std::ref( fut ) );			 // Send future to new thread

	std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
	prom.set_value( "Hello There" );                            // Fulfill promise
	
	th.join();

	return 0;
}