#ifndef __SYNC_QUEUE_H__
#define __SYNC_QUEUE_H__

#include <queue>

#include "expression_tree.h"
#include "link_val.h"

using namespace std;

struct update {
    void *address;
    link_val new_value;
};


/**
 * sync_queue.h - The synchronized queue that will be used for the producer
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
