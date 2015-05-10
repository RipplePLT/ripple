#ifndef __FILE_LIB_H__
#define __FILE_LIB_H__

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

namespace file_lib {

    bool contains_word(string line, string word);

    int length(string line);
    int locate_word(string line, string word);

    void print_line(string line);

}

#endif