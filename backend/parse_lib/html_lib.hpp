#ifndef HTML_LIB_HPP
#define HTML_LIB_HPP

#include <stack>
#include <string>
#include <vector>

using namespace std;

static void empty_stack();

namespace html_lib {

    bool contains_tag(string line, string tag);
    bool contains_word(string line, string word);
    string get_body(string line);
    vector<string> get_collection(string line, string tag);
    string get_head(string line);
    int get_num_tags(string line, string tag);
    string get_tag(string line, string tag);
    int size(string line);

}

#endif