#include "xml_lib.hpp"

using namespace std;

static stack<string> parse_stack;

static void empty_stack() {

    while (!parse_stack.empty()) {
        parse_stack.pop();
    }
}

bool xml_lib::contains_tag(string line, string tag) {
    return line.find(tag) > 0 ? true : false;
}

bool xml_lib::contains_word(string line, string word) {
    return line.find(word) > 0 ? true : false;
}

vector<string> xml_lib::get_collection(string line, string tag) {
    empty_stack();
    vector<string> nodes;
    return nodes;
}

string xml_lib::get_node(string line, string tag) {
    empty_stack();
    return "";
}

string xml_lib::get_node_text(string line, string tag) {
    empty_stack();
    return "";
}

int xml_lib::get_num_nodes(string line, string tag) {
    empty_stack();
    int count = 0;
    return count;
}

string xml_lib::get_root(string line, string tag) {
    empty_stack();
    return "";
}

int xml_lib::size(string line) {
    empty_stack();
    int count = 0;
    return count;
}
