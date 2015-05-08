#ifndef STREAM_READER_HPP
#define STREAM_READER_HPP

#include <pthread.h>
#include <iostream>    

using namespace std;

template <typename T>
struct FuncPtr {
    typedef T (*Type)(std::string a);
};


template <typename T>
class StreamReader {

    public:

        StreamReader(){
            this->stop_stream = false;
        }

        ~StreamReader(){
            this->stop_stream = true;
            pthread_join(stream_thread, NULL);
            cout << "thread joined" << endl;
        }

        virtual void start_thread()=0;

    protected:

        typename FuncPtr<T>::Type ptr;
        pthread_t stream_thread;
        bool stop_stream;
        virtual void run_stream_thread()=0;
};

#endif
