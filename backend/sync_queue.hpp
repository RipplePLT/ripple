#ifndef SYNC_QUEUE_HPP
#define SYNC_QUEUE_HPP

#include <queue>

#include "variable_tree.hpp"

using namespace std;

struct update {
    void *address;
    struct link_val new_value;
};


/**
 * sync_queue.hpp - The synchronized queue that will be used for the producer
 * consumer model between the select thread and the main thread.
 *
 * Author: Alexander Roth
 * Date:   2015-04-09
 **/

class sync_queue {
    private:
        queue<struct update> *update_queue;
        int size;
    public:
        sync_queue();
        sync_queue(int size);
        ~sync_queue();
        void push(struct update info);
        struct update pop();
        bool empty();
        int get_size();
};

#endif
