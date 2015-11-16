#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> foo(0);
int i = 0;

void set_foo(int x) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	foo.store(x);
	// foo = x;
}

void print_foo() {
	 int x;
	 do{
		++i;
		x = foo.load();
		std::cout << "repeates " << i << '\n';
	//	x = foo;
	} while (x == 0); 
	
	/*while (foo == 0){
		++i;
		std::cout << "yields " << i << '\n';
		std::this_thread::yield();
	}*/
	std::cout << "foo: " << x << '\n';
	// std::cout << "foo: " << foo << '\n';
}

int main(){
	std::thread th1(print_foo);
	std::thread th2(set_foo, 10);

	th1.join();
	th2.join();

	return 0;
}