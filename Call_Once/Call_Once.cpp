// call_once example

// Once_flag objects are used as arguments for call_once.
// Using the same object on different calls to call_once in different threads 
// causes a single execution if called concurrently.

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::milliseconds
#include <mutex>          // std::call_once, std::once_flag
#include <vector>
#include <array>

int winner;
std::once_flag winner_flag;

void set_winner( int x ) {
	winner = x;
}

void wait_1000ms( int id ) {
	std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
	std::call_once( winner_flag, set_winner, id ); 
}

int main() {
	// std::thread threads[10];
	std::array<std::thread, 10> threads;
	
	for( int i=0; i<10; ++i )
		threads[i] = std::thread( wait_1000ms, i+1 );
	
	/*std::vector<std::thread> threads;
	for( int i = 0; i < 10; ++i )
		threads.push_back( std::thread( wait_1000ms, i+1 ) );*/

	std::cout << "waiting for the first among 10 threads to count 1000 ms... \n";

	for( auto& th : threads )
		th.join();

	std::cout << "winner thread: " << winner << '\n';

	return 0;
}