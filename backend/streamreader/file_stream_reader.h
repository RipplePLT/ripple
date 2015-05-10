#ifndef __FILE_STREAM_READER_H__
#define __FILE_STREAM_READER_H__

#include <fstream> 
#include <sstream>
#include "stream_reader.h"

template <typename T>
class FileStreamReader : StreamReader<T>{

private:
    ifstream file_stream; 
    string file_path;
    string delimiter;

public:
    FileStreamReader<T>(void *to_update, typename FuncPtr<T>::f_ptr f = nullptr, string file_path="", int interval=0, const string delim = "\0") {
        this->to_update = (T *)to_update; 
        this->filter_func_ptr = f;
        this->file_path = file_path;
        this->interval = interval;
        this->delimiter = delim;
    }

   ~FileStreamReader<T>() {};

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
        static_cast<FileStreamReader*>(p)->run_stream_thread();
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
            
            file_stream.open(file_path, ios::in | ios::binary);

            //File failed to open, die
            if (!file_stream.is_open()) {
                cerr << "File not opened properly" << endl;
                exit(1);
            }

            if (delimiter == "\0") {
                file_stream.seekg(0, ios::end);
                read_buffer.resize(file_stream.tellg());
                file_stream.seekg(0, ios::beg);
                file_stream.read(&read_buffer[0], read_buffer.size());
                file_stream.close();

                if (file_stream.fail()) {
                    cerr << "File I/O error" << endl;
                    exit(1);
                }

                *this->to_update = this->filter_func_ptr(read_buffer);
                linked_var::update_nonlinked_var(this->to_update);

            } else {
                while(getline(file_stream, read_buffer, *delimiter.c_str())) {

                    if (file_stream.fail()) {
                        cerr << "File I/O error" << endl;
                        exit(1);
                    }
                    cout << read_buffer << endl;
                 //   *this->to_update = this->filter_func_ptr(read_buffer)
                 //   linked_var::update_nonlinked_var(this->to_update);
                }
            }
            if (this->interval)
                sleep(this->interval);
        }
    }
};
#endif

