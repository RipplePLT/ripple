#ifndef __XML_LIB_H__
#define __XML_LIB_H__

#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

static void empty_stack();

namespace xml_lib {

    bool contains_tag(string line, string tag);
    bool contains_word(string line, string word);

    int get_num_nodes(string line, string tag);
    int locate_word(string line, string word);
    int size(string line);
     
    string get_node(string line, string tag);
    string get_node_text(string line, string tag);
       
    vector<string> get_collection(string line, string tag);
    
    void print_line(string line);

}

#endif
