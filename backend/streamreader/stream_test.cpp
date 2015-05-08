#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include "web_stream_reader.hpp"

using namespace std;

int test_func(string msg){
    cout << msg << endl;
    return 1;
}


int main(){
    string tmp;

    int count = 0;
    int count2 = 0;
    int to_update = 0;


    FuncPtr<int>::Type f;
    f = &test_func;
    WebStreamReader<int> *streamy = new WebStreamReader<int>("www.google.com", f);

    streamy->start_thread();

    while(1){
        if(count ==  1000000){
 //           cout << count << endl;
            count = 0;
            count2++;
        }else{
            count++;
        }
        if(count2 > 10000)
            break;

    }

}
