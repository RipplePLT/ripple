#ifndef FILE_STREAM_READER_HPP
#define FILE_STREAM_READER_HPP

#include <string>
#include <iostream>
#include <fstream> 
#include "stream_reader.hpp"

class WebStreamReader {

    public:
        FileStreamReader(string file_name);
        ~FileStreamReader();

    protected:
        void run_stream_thread();

    private:
        ofstream read_file; 
        string file_name;

        
};

#endif

