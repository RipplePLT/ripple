#include "web_stream_reader.hpp"

WebStreamReader::WebStreamReader(string URL, int port){
    //Instantiate function and have it run function run_stream_thread
    this->stream_thread = new thread(&WebStreamReader::run_stream_thread, this);
    //Create HTTP request
    
}

WebStreamReader::~WebStreamReader(){

}

WebStreamReader::run_stream_thread(){
    
    //Continuously connect to webpage
    while(1){

        char responsep[51201] = "";
        ssize_t n;
        while((n = recv(socket, response, 51200, 0)) > 0){
            if(n == -1){
                perror("Error receiving data from webpage");
                exit(1);
            }

        }

    }
}


