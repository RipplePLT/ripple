#ifndef __XML_LIB_H__
#define __XML_LIB_H__

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

static void empty_stack();

namespace ripple {

    int get_num_nodes(string line, string tag);
     
    string get_node(string line, string tag);
    string get_node_text(string line, string tag);
       
}

#endif
