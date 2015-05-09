#ifndef FILE_STREAM_READER_HPP
#define FILE_STREAM_READER_HPP

#include <string>
#include <fstream> 
#include <sstream>
#include "stream_reader.hpp"

template <typename T>
class FileStreamReader : StreamReader<T>{

    public:
        FileStreamReader<T>(string file_path, typename FuncPtr<T>::f_ptr f = NULL, int interval=0, const string delim = "\0"){
            this->file_path = file_path;
            this->interval = interval;
            this->aux_func_ptr = f;
            this->delimiter = delim;
        }

        FileStreamReader<T>(string file_path, int interval=0, const string delim = "\0") {
            this->file_path = file_path;
            this->interval = interval;
            this->delimiter = delim;
        }

        FileStreamReader<T>(string file_path, const string delim){
            this->file_path = file_path;
            this->delimiter = delim;
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
                
                file_stream.open(file_path, ios::in | ios::binary);

                //File failed to open, die
                if(!file_stream.is_open()){
                    cout<< "File not opened properly" << endl;
                    break;
                }

                if(delimiter == "\0"){
                    file_stream.seekg(0, ios::end);
                    read_buffer.resize(file_stream.tellg());
                    file_stream.seekg(0, ios::beg);
                    file_stream.read(&read_buffer[0], read_buffer.size());
                    file_stream.close();

                    if(this->aux_func_ptr){
                        /*update*/this->aux_func_ptr(read_buffer);
                    }else{
                        //update(read_buffer);
                    }
                }else{
                    while(getline(file_stream, read_buffer, *delimiter.c_str())){
                        if(this->aux_func_ptr){
                            /*update*/this->aux_func_ptr(read_buffer);
                        }else{
                            cout << read_buffer << endl;
                            //update(read_buffer);
                        }
                    }
                }

                if(this->interval)
                    sleep(this->interval);
            }
        }

    private:
        ifstream file_stream; 
        string file_path;
        string delimiter;
};
#endif

