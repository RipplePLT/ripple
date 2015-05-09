#ifndef LINK_UPDATE_THREAD_HPP
#define LINK_UPDATE_THREAD_HPP

#include <thread>

#include "sync_queue.hpp"

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
