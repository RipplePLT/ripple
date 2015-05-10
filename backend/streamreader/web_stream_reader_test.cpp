#include "web_stream_reader.hpp"
#include <curl/curl.h>

int main(){
    WebStreamReader *stream = new WebStreamReader("www.cs.columbia.edu");
    stream->run_curl();
    stream->start_thread();
    

    int count = 0;
    int count2 = 0;
    while(1){
        if(count2 > 10)
            break;
        if(count < 10000000){
            count++;
        }else{
            count = 0;
            count2++;
        }
   }         

    cout << "ended while" << endl;

    return 0;
}
