#ifndef __FILE_LIB_H__
#define __FILE_LIB_H__

#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace ripple {

    bool contains_word(std::string line, std::string word);

    int length(std::string line);
    int locate_word(std::string line, std::string word);

    void print_line(std::string line);

}

#endif
