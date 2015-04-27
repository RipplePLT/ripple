#include <iostream>
#include <thread>

#include "sync_queue.hpp"

using namespace std;

void worker_thread(bool test) {
    cout << "In worker thread" << endl;
    cout << "Test value: " << test << endl;
}

void consume(bool working, sync_queue& queue) {
    while (working) {
        while (!queue.empty()) {
            // TODO: Tom put your code here for updating the thread.
            // struct update info = queue.pop()
            cout << "Updating" << endl;
        }
    }
}


int main() {
    bool test = false;
    sync_queue t1;

    std::thread worker(consume, test, t1);
    worker.join();
}
