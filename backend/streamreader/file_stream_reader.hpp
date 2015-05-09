#ifndef FILE_STREAM_READER_HPP
#define FILE_STREAM_READER_HPP

#include <string>
#include <fstream> 
#include "stream_reader.hpp"

template <typename T>
class FileStreamReader : StreamReader<T>{

    public:
        FileStreamReader<T>(string file_path, int interval=0, typename FuncPtr<T>::Type f = NULL){
            this->file_path = file_path;
            this->interval = interval;
            this->ptr = f;
        }

        ~FileStreamReader<T>(){};

        void start_thread(){
            pthread_create(&(this->stream_thread), NULL, this->run_stream_thread_proxy, this);
        }

    protected:
        //Proxy function to allow pthread to run on member variable
        static void* run_stream_thread_proxy(void *p){
            static_cast<FileStreamReader*>(p)->run_stream_thread();
            return NULL;
        }

        void run_stream_thread(){
            
            string read_buffer;

            while(1){
                if(this->stop_stream)
                    break;
                
                cout << read_buffer << endl;

                //Runs update method on linked variable
                if(this->ptr)
                    this->ptr("Page Loaded and Printed");

                if(this->interval)
                    sleep(this->interval);
            }
        }

    private:
        ofstream read_file; 
        string file_path;

        
};
#endif

