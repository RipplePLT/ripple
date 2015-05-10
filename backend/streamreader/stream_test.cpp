#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include "web_stream_reader.h"
#include "file_stream_reader.h"

using namespace std;

int test_func(string msg){
    cout << msg << endl;
    return 1;
}

/*int test_1(){
    string tmp;

    int count = 0;
    int count2 = 0;
    int to_update = 0;


    FuncPtr<int>::f_ptr f;
    f = &test_func;
    WebStreamReader<int> *streamy = new WebStreamReader<int>("asopidgjewoiprj", 8001, f);

    streamy->start_thread();

    while(1){
        if(count ==  1000000){
            count = 0;
            count2++;
        }else{
            count++;
        }
        if(count2 > 10000)
            break;

    }
    
    return 0;
    
}*/

//This method is not to be run, we want to see if all 
//Combinations of declarations are possible
void compilation_test(){
    unsigned int port = 2;
    FuncPtr<int>::f_ptr f;
    f = &test_func;


}

int main(){
    string tmp;

    int count = 0;
    int count2 = 0;
    int to_update = 0;

    FuncPtr<int>::f_ptr f;
    f = &test_func;

    FileStreamReader<int> *streamy = new FileStreamReader<int>("test1.txt", f);
    
    FileStreamReader<int> *streamy2 = new FileStreamReader<int>("test2.txt", f);

    streamy->start_thread();

    streamy2->start_thread();
    while(1){
        if(count ==  1000000){
            count = 0;
            count2++;
        }else{
            count++;
        }
        if(count2 > 10000)
            break;

    }


}
