#ifndef __RIPPLE_HEADER_H__
#define __RIPPLE_HEADER_H__

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

#include "expression_tree.h"
#include "file_lib.h"
#include "html_lib.h"
#include "link_val.h"
#include "linked_var.h"
#include "xml_lib.h"
#include "keyboard_stream_reader.h"
#include "web_stream_reader.h"
#include "file_stream_reader.h"

using namespace ripple;

namespace ripple {
    string input(string p){
        string x;
        cout << p;
        cout.flush();
        cin >> x;
        return x;
    }
}

string default_rpl_str_str(string xyzder){ return xyzder; }
int str_to_int(string xyzder) { return stoi(xyzder); }
float str_to_float(string xyzder) { return stof(xyzder); }
// Used for short-term manipulation of linked vars
linked_var *universal_linked_var_ptr;

#endif
