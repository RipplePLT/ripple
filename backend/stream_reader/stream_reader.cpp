#include "stream_reader.hpp"

/*
 *
 */
StreamReader::StreamReader(int* update){
    cout << "Constructor ran" << endl;
    this->stop_thread = false;
    this->to_update = update;
    //Instantiate function and have it run function run_stream_thread
    this->stream_thread  = new thread(&StreamReader::run_stream_thread, this);
}

StreamReader::~StreamReader(){
    cout << "destructor ran" << endl;
    this->stop_thread = true;
    this->stream_thread->join();
    cout << "thread joined" << endl;
}

/*
 *Runs stream_reader code
 */
void StreamReader::run_stream_thread(){
    string tmp = "";
    cout << "run_stream_thread ran" << endl;
    int counter = 0;

    while(1){
        if(!stop_thread)
            break;

        counter++;
        if(counter == 100000000){
            counter = 0;
        }else{
            *to_update = counter;
        }
    }


}
