#ifndef __STREAM_READER_H__
#define __STREAM_READER_H__

#include <pthread.h>
#include <iostream>    
#include <unistd.h>
#include <string>

using namespace std;

template <typename T>
struct FuncPtr {
    typedef T (*f_ptr)(std::string a);
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
    }

    virtual void start_thread()=0;

protected:
    typename FuncPtr<T>::f_ptr aux_func_ptr;
    pthread_t stream_thread;
    bool stop_stream;
    int interval;
    virtual void run_stream_thread()=0;
};

#endif
