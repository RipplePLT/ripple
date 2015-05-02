#ifndef XML_LIB_HPP
#define XML_LIB_HPP

#include <stack>
#include <string>

namespace xml_lib {

    string get_root(string tag);
    string get_node(string tag);
    string get_node_text(string tag);
       
}

#endif
