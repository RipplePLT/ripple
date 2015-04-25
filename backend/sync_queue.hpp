#ifndef SYNC_QUEUE_HPP
#define SYNC_QUEUE_HPP

#include <queue>

#include "linked_var"

/**
 * sync_queue.hpp - The synchronized queue that will be used for the producer
 * consumer model between the select thread and the main thread.
 *
 * Author: Alexander Roth
 * Date:   2015-04-09
 **/
using namespace std;

class sync_queue {
    private:
        queue<linked_var> sync_queue {nullptr};
        int size;
    public:
        sync_queue(int size);
        ~sync_queue();
        void push(linked_var item);
        linked_var pop();
}

#endif
