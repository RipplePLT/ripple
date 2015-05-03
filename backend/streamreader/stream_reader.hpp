#ifndef STREAM_READER_HPP
#define STREAM_READER_HPP

#include <thread>
#include <functional>
#include <iostream>    

using namespace std;

class StreamReader {

    public:
        StreamReader();
        ~StreamReader();

        virtual void start_thread()=0;
    protected:
        thread *stream_thread;
        bool stop_stream;
        virtual void run_stream_thread()=0;
};

#endif
