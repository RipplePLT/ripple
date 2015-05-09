#ifndef STREAM_READER_HPP
#define STREAM_READER_HPP

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
