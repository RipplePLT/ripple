#ifndef WEB_STREAM_READER_HPP
#define WEB_STREAM_READER_HPP

#include <string>
#include <curl/curl.h>
#include "stream_reader.hpp"

template <typename T>
class WebStreamReader : StreamReader<T>{

    public:
        WebStreamReader(string URL, typename FuncPtr<T>::Type f){
            this->URL = URL;
            this->ptr = f;
        }

        ~WebStreamReader(){}

        void start_thread(){
            pthread_create(&(this->stream_thread), NULL, this->run_thread, this);
        }

    protected:

        static void* run_thread(void *p){
            static_cast<WebStreamReader*>(p)->run_stream_thread();
            return NULL;
        }

        //Used by CURL to write the data it reads into a string
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
            ((string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        }

        void run_stream_thread(){
            cout << "this ran from run_stream_thread()" << endl;
            string readBuffer;
            int count = 0;
            while(1){
                if(this->stop_stream)
                    break;
                
                curl = curl_easy_init();
                if(curl){
                    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebStreamReader::WriteCallback);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                    res = curl_easy_perform(curl);
                    cout<<readBuffer<<endl;

                }

                curl_easy_cleanup(curl);
                count++;
                cout << "Grabbed next page" << count << endl;

                if(this->ptr("we got a func"))
                    cout << this->ptr("") << endl;
                    cout << "we returned an int" << endl;
            }
        }

    private:
        string URL;
        CURL *curl;
        CURLcode res;
};
#endif
