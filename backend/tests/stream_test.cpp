#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include "stream_reader.h"

using namespace std;

int main(){
    string tmp;

    int count = 0;
    int count2 = 0;
    int to_update = 0;
    StreamReader *streamy = new StreamReader(&to_update);

    while(1){
        if(count ==  100000000){
            cout << count << endl;
            count = 0;
            count2++;
        }else{
            count++;
        }
        if(count2 > 1)
            break;

    }

}
