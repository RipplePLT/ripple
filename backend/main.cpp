#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ValNode.hpp"

using namespace std;

mutex m;
condition_variable cv;	// 

/*
 * Handle all updates of linked variables.
 */
void worker_thread()
{
	cout << "begin worker thread\n";
	unique_lock<mutex> lock;
	for (;;) {
		lock.lock();
		
		cv.wait(lock);

		cout << "Var changed!";
		lock.unlock();
	}
}

int main()
{
	// int deg_f = 50;

	cout << "start\n";
	// Create thread to handle data updates
	thread worker(worker_thread);
	cout << "created thread\n";
	worker.join();
/*
	
	for (;;) {
		sleep(1);
		cv.notify_one();
	}

*/

	return 0;
}
