#ifndef __LINK_UPDATE_THREAD_H__
#define __LINK_UPDATE_THREAD_H__

#include <thread>

#include "sync_queue.h"

using namespace std;

class link_update_thread {
    private:
        thread updater;
    public:
        link_update_thread();
        ~link_update_thread();
        void run(bool working, sync_queue& queue);
};

#endif
