#ifndef __STREAM_READER_H__
#define __STREAM_READER_H__

#include <thread>
#include <string>
#include <iostream>

using namespace std;

class StreamReader {
    private:
//        ifstream istream;
        thread *stream_thread;
        int* to_update;
        bool stop_thread;

    public:

        StreamReader(int* update);
        ~StreamReader();
        void run_stream_thread();


};

#endif
