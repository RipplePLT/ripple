#ifndef __WEB_STREAM_READER_H__
#define __WEB_STREAM_READER_H__

#include <vector>
#include "stream_reader.h"
#include <curl/curl.h>

#define ERROR_BUF_SIZE 1024

template <typename T>
class WebStreamReader : StreamReader<T>{

private:
    unsigned int port;
    string URL;
    CURL *curl;
    CURLcode curl_result;

public:
    WebStreamReader(void *to_update, typename FuncPtr<T>::f_ptr f = nullptr, 
                string URL = nullptr, unsigned int port = 80, int interval = 0) {
        this->to_update = (T *)to_update; 
        this->filter_func_ptr = f;
        this->URL = URL;
        this->port = port;
        this->interval = interval;
    }

    ~WebStreamReader() {}

    /*
     * Public accessor function used to begin running the instantiated WebStreamReader.
     */
    void start_thread() {
        if (pthread_create(&(this->stream_thread), NULL, this->run_stream_thread_proxy, this)) {
            cerr << "Could not create StreamReader" << endl;
            exit(1);
        }
    }

protected:
    /*
     * This function is called from start_thred(), as p_threads in c++ 
     * cannot be called directly on member functions due to their implicit 
     * this-> accessor. Declarating this function as static acts as workaround 
     * that enables the ability to call the non-static function run_stream_thread.
     */
    static void* run_stream_thread_proxy(void *p) {
        static_cast<WebStreamReader*>(p)->run_stream_thread();
        return NULL;
    }

    /*
     * Auxiliary function to be used by cURL library. Determines size of the data read
     * in by curl, which allows this data to be written to a string.
     */
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        ((string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    //pthread runs this function to continuously get and pass webpage to either the function or something else
    void run_stream_thread() {
        string read_buffer;
        vector<char> error_buffer(ERROR_BUF_SIZE);
        int count = 0;

        while(1) {
            if (this->stop_stream)
                break;
            
            curl = curl_easy_init();

            //Set cURL options
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error_buffer[0]);
                curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());

                if (port)
                    curl_easy_setopt(curl, CURLOPT_PORT, port);

                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WebStreamReader::WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
                curl_result = curl_easy_perform(curl);
            }
            
            curl_easy_cleanup(curl);

            //Result is set to something other than 0 - there was an error so print and exit program
            if (curl_result) {
                cerr<<"Error from StreamReader " << URL << ": " <<  curl_easy_strerror(curl_result) << endl;
                exit(1);
            }
                
            *this->to_update = this->filter_func_ptr(read_buffer);
            linked_var::update_nonlinked_var(this->to_update);

            if (this->interval)
                sleep(this->interval);
        }
    }
};
#endif
