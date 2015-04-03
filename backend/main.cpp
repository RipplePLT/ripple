#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "ValNode.hpp"

// @TODO use producer-consumer queue

using namespace std;

mutex m;
condition_variable cv;

/*
 * Handle all updates of linked variables.
 */
void worker_thread()
{
	unique_lock<mutex> lock(m, defer_lock);
	for (;;) {
		lock.lock();
		
		cv.wait(lock);
		cout << "Var changed!\n";
		lock.unlock();
	}
}

int main()
{
	thread worker(worker_thread);
	
	for (;;) {
		sleep(1);
		cv.notify_one();
	}

	worker.join();

	return 0;
}
