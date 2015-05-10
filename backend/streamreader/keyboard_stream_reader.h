#ifndef __KEYBOARD_STREAM_READER_H__
#define __KEYBOARD_STREAM_READER_H__

#include <fstream> 
#include <sstream>
#include "stream_reader.h"

template <typename T>
class KeyboardStreamReader : StreamReader<T>{

    public:

        KeyboardStreamReader<T>(typename FuncPtr<T>::f_ptr f = nullptr) {
            this->aux_func_ptr = f;
        }

       ~KeyboardStreamReader<T>() {};

        /*
         *Public accessor function used to begin running the instantiated WebStreamReader.
         */
        void start_thread() {
            if (pthread_create(&(this->stream_thread), NULL, this->run_stream_thread_proxy, this)) {
                cerr << "Could not create StreamReader" << endl;
                exit(1);
            }
        }

    protected:

        /*
         *This function is called from start_thred(), as p_threads in c++ 
         *cannot be called directly on member functions due to their implicit 
         *this-> accessor. Declarating this function as static acts as workaround 
         *that enables the ability to call the non-static function run_stream_thread.
         */
        static void* run_stream_thread_proxy(void *p) {
            static_cast<KeyboardStreamReader*>(p)->run_stream_thread();
            return NULL;
        }

        /*
         *Function that does work of the thread. Work done in a permanent while loop that will
         *continuously update a linked variable. 
         *
         *File and file i/o errors cause the process to exit. Depending on arguments of function,
         *either entire file or character-delimited strings will be read from a file. 
         */
        void run_stream_thread() {
            
            string read_buffer;

            while(1) {
                if (this->stop_stream)
                    break;
                
                string line; 
                getline(cin, line);
                    

                if (this->aux_func_ptr)
                    this->aux_func_ptr(line);
            }
        }

    private:
        ifstream in_stream; 
};
#endif



