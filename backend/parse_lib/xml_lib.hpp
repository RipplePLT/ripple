#ifndef XML_LIB_HPP
#define XML_LIB_HPP

#include <stack>
#include <string>
#include <vector>

using namespace std;

static void empty_stack();

namespace xml_lib {

    bool contains_tag(string line, string tag);
    bool contains_word(string line, string word);
    vector<string> get_collection(string line, string tag);
    string get_node(string line, string tag);
    string get_node_text(string line, string tag);
    int get_num_nodes(string line, string tag);
    string get_root(string line, string tag);
    int size(string line);
       
}

#endif
