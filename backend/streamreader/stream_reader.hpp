#ifndef STREAM_READER_HPP
#define STREAM_READER_HPP

#include <pthread.h>
#include <functional>
#include <iostream>    

using namespace std;

class StreamReader {

    public:
        StreamReader();
        ~StreamReader();

        virtual void start_thread()=0;
    protected:
        pthread_t stream_thread;
        bool stop_stream;
        virtual void run_stream_thread()=0;
};

#endif
