#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include "web_stream_reader.h"
#include "file_stream_reader.h"
#include "keyboard_stream_reader.h"

using namespace std;

int int_test_func(string msg){
    cout << "Test func message: " << msg << endl;
    return 1;
}

/*float float_test_func(string msg){}

bool bool_test_func(string msg){}

string string_test_func(string msg){}
*/
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
    f = &int_test_func;


}

int main(){
    string tmp;

    int count = 0;
    int count2 = 0;
    int to_update = 0;

    FuncPtr<int>::f_ptr f;
    f = &int_test_func;

    FuncPtr<int>::f_ptr g;
    g = NULL;



    KeyboardStreamReader<int> *streamy = new KeyboardStreamReader<int>(f);

    streamy->start_thread();

    FileStreamReader<int> *streamy1 = new FileStreamReader<int>("test1.txt", g, 2);
    
    FileStreamReader<int> *streamy2 = new FileStreamReader<int>("test2.txt", g, 2);    

    streamy1->start_thread();

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
