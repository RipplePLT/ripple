#include "stream_reader.hpp"

StreamReader::StreamReader(){
    this->stop_stream = false;
}

StreamReader::~StreamReader(){
    this->stop_thread = true;
    this->stream_thread->join();
}

