// condition_variable example
//A condition variable is an object able to block the calling thread until notified to resume.
//It uses a unique_lock (over a mutex) to lock the thread when one of its wait functions is called. 
//The thread remains blocked until woken up by another thread that calls a notification function on the same condition_variable object.

#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
	std::unique_lock<std::mutex> lck(mtx);
	while (!ready) 
		cv.wait(lck);
	std::cout << "thread " << id << '\n';
}

void go() {
	std::unique_lock<std::mutex> lck(mtx);
	ready = true;
	cv.notify_all();
}

int main()
{
	std::thread threads[10];
	for (int i = 0; i<10; ++i)
		threads[i] = std::thread(print_id, i);

	std::cout << "10 threads ready to race...\n";  
	go();

	for (auto& th : threads) 
		th.join();

	return 0;
}