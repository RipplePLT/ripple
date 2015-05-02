#ifndef WEB_STREAM_READER_HPP
#define WEB_STREAM_READER_HPP

#include <string>
#include <iostream>
#include "stream_reader.hpp"

class WebStreamReader {

    public:
        WebStreamReader(string URL, int port);
        WebStreamReader(string URL);
        ~WebStreamReader();

    protected:
        void run_stream_thread();

    private:
        const int port = 80; 
        
};

#endif
