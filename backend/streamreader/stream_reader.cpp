#include "stream_reader.hpp"

StreamReader::StreamReader(){
    this->stop_stream = false;
}

StreamReader::~StreamReader(){
    this->stop_stream = true;
    this->stream_thread->join();
}

