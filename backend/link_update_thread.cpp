#include "link_update_thread.h"

#include <mutex>

using namespace std;

link_update_thread::link_update_thread() {
}

link_update_thread::~link_update_thread() {
    this->updater.join();
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
    sync_queue test_queue;
    thread t(consume, test, test_queue);
    t.join();
    return 0;
}

/*
void link_update_thread::run(bool working, sync_queue& queue) {
    this->updater = thread(consume, working, queue);
}
*/

