#ifndef __STREAM_READER_H__
#define __STREAM_READER_H__

#include <pthread.h>
#include <iostream>    
#include <unistd.h>
#include <string>

#include "../linked_var.h"

using namespace std;

/*
 * Template used to define a variable type function pointer.
 * Used to pass what stream reads to be parsed
 */
template <typename T>
struct FuncPtr {
    typedef T (*f_ptr)(string argument);
};

/*
 * Base class for StreamReaders that declares member variables that are
 * used in the derived classes
 */
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
    T* to_update;
    typename FuncPtr<T>::f_ptr filter_func_ptr;
    pthread_t stream_thread;
    bool stop_stream;
    int interval;
    virtual void run_stream_thread()=0;
};

#endif
