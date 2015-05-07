#include "stream_reader.hpp"

StreamReader::StreamReader(){
    this->stop_stream = false;
}

StreamReader::~StreamReader(){
    this->stop_stream = true;
    pthread_join(stream_thread, NULL);
    cout << "thread joined" << endl;
}

