#ifndef WEB_STREAM_READER_HPP
#define WEB_STREAM_READER_HPP

#include <string>
#include <iostream>
#include <curl/curl.h>
#include "stream_reader.hpp"

class WebStreamReader : StreamReader{

    public:
        WebStreamReader(string URL);
        ~WebStreamReader();

        //void testCurl();
        void start_thread();
        void run_curl();
    protected:
        void run_stream_thread();
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
        size_t curl_to_string(void *ptr, size_t size, size_t nmemb, void *data);
    private:
        string URL;
        CURL *curl;
        CURLcode res;

};
#endif
