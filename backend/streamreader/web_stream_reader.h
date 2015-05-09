#ifndef WEB_STREAM_READER_H
#define WEB_STREAM_READER_H

#include <string>
#include <curl/curl.h>
#include <vector>
#include "stream_reader.h"

#define ERROR_BUF_SIZE

template <typename T>
class WebStreamReader : StreamReader<T>{

    public:
        WebStreamReader(string URL, int interval = 0, typename FuncPtr<T>::f_ptr f = NULL, unsigned int port = 80){
            this->URL = URL;
            this->port = port;
            this->interval = interval;
            this->aux_func_ptr = f;
        }

        WebStreamReader(string URL, typename FuncPtr<T>::f_ptr f = NULL, int interval = 0){
            this->URL = URL;
            this->aux_func_ptr = f;
            this->interval = interval;
        }

        WebStreamReader(string URL, unsigned int port){
            this->URL = URL;
            this->port = port;
        }

        ~WebStreamReader(){}

        void start_thread(){
            pthread_create(&(this->stream_thread), NULL, this->run_stream_thread_proxy, this);
        }

    protected:

        //Workaround to call pthread on a member function
        static void* run_stream_thread_proxy(void *p){
            static_cast<WebStreamReader*>(p)->run_stream_thread();
            return NULL;
        }

        //Used by CURL to write the data it reads into a string
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
            ((string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        }

        //pthread runs this function to continuously get and pass webpage to either the function or something else
        void run_stream_thread(){
            string read_buffer;
            vector<char> error_buffer(ERROR_BUF_SIZE);
            int count = 0;

            while(1){
                if(this->stop_stream)
                    break;
                
                curl = curl_easy_init();
                if(curl){
                    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error_buffer[0]);
                    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

                    if(port)
                        curl_easy_setopt(curl, CURLOPT_PORT, port);

                    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebStreamReader::WriteCallback);
                    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
                    curl_result = curl_easy_perform(curl);
                }
                
                curl_easy_cleanup(curl);

                //Result is set to something other than 0 - there was an error
                if(curl_result)
                    cerr<<"Error from StreamReader " << URL << ": " <<  curl_easy_strerror(curl_result) << endl;

                cout << read_buffer << endl;

                //Runs update method on linked variable
                if(this->aux_func_ptr)
                    this->aux_func_ptr("Page Loaded and Printed");

                if(this->interval)
                    sleep(this->interval);
            }
        }

    private:
        unsigned int port;
        string URL;

        CURL *curl;
        CURLcode curl_result;
};
#endif
