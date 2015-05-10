#ifndef __HTML_LIB_H__
#define __HTML_LIB_H__

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

static void empty_stack();

namespace ripple {

    bool contains_tag(std::string line, std::string tag);

    int get_num_tags(std::string line, std::string tag);
    int size(std::string line);

    std::string get_body(std::string line);
    std::string get_head(std::string line);
    std::string get_tag(std::string line, std::string tag);

    std::string trim(std::string line);
}

#endif
