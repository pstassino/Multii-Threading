// packaged_task example


#include <iostream>     // std::cout
#include <future>       // std::packaged_task, std::future
#include <chrono>       // std::chrono::seconds
#include <thread>       // std::thread, std::this_thread::sleep_for

// count down taking a second for each value:
int countdown( int from, int to ) {
	for( int i=from; i!=to; --i ) {
		std::cout << i << '\n';
		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}
	std::cout << "Lift off!\n";
	return from - to;
}

int main() {
	std::packaged_task<int( int, int )> tsk( countdown );   // Set up packaged_task in the main thread
	std::future<int> ret = tsk.get_future();                // Get future

	std::thread th( std::move( tsk ), 10, 0 );              // Spawn a thread to count down from 10 to 0
	// ...
	int value = ret.get();                                  // Wait for the task to finish and get result

	std::cout << "The countdown lasted for " << value << " seconds.\n";
	th.join();

	return 0;
}