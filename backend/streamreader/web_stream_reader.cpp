#include "web_stream_reader.hpp"

WebStreamReader::WebStreamReader(string URL){
    this->URL = URL;
}

WebStreamReader::~WebStreamReader(){}


void WebStreamReader::start_thread(){
    //Instantiate function and have it run function run_stream_thread
    pthread_create(&stream_thread, NULL, WebStreamReader::run_thread, this);
}


void* WebStreamReader::run_thread(void *p){
    static_cast<WebStreamReader*>(p)->run_stream_thread();
    return NULL;

}


size_t WebStreamReader::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


//Does not work because threads
void WebStreamReader::run_stream_thread(){
    cout << "this ran from run_stream_thread()" << endl;
    string readBuffer;
    int count = 0;
    while(1){
        if(stop_stream)
            break;
        
        curl = curl_easy_init();
        if(curl){
            curl_easy_setopt(curl, CURLOPT_URL, "www.cs.columbia.edu/~jae/");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebStreamReader::WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            cout<<readBuffer<<endl;

        }
        readBuffer = "";
        curl_easy_cleanup(curl);
        count++;
        cout << "Grabbed next page" << count << endl;
    }
}


