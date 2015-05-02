#ifndef STREAM_READER_HPP
#define STREAM_READER_HPP

#include <thread>
#include <functional>

using namespace std;

virtual class StreamReader {

    public:
        StreamReader(void *func());
        ~StreamReader();

    protected:
        thread *stream_thread;
        bool stop_stream;
        void* func;
        virtual void run_stream_thread();
};

#endif
