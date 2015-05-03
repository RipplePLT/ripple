#include "web_stream_reader.hpp"

WebStreamReader::WebStreamReader(string URL){
    this->URL = URL;
}


WebStreamReader::~WebStreamReader(){}

void WebStreamReader::start_thread(){
    //Instantiate function and have it run function run_stream_thread
    stream_thread = new thread(&WebStreamReader::run_stream_thread, this);
}

size_t WebStreamReader::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

//Works
void WebStreamReader::run_curl(){
    string readBuffer;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebStreamReader::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        cout<<readBuffer<<endl;

    }
    curl_easy_cleanup(curl);


}

//Does not work because threads
void WebStreamReader::run_stream_thread(){
    string readBuffer;
    curl = curl_easy_init();
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebStreamReader::WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        cout<<readBuffer<<endl;

    }
    curl_easy_cleanup(curl);
}

