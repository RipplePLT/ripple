#include "xml_lib.h"
#include "file_lib.h"
#include "html_lib.h"

using namespace std;

static stack<string> parse_stack;


static void empty_stack() {

    while (!parse_stack.empty()) {
        parse_stack.pop();
    }
}


int ripple::get_num_nodes(string line, string tag) {
    empty_stack();

    int count = 0;

    string start_tag = "<" + tag + ">";
    string end_tag = "</" + tag + ">";

    stringstream node_stream(line);
    string word;

    for (; node_stream >> word; ) {
        if (word == start_tag) {
            parse_stack.push(word);
        } else if (word == end_tag && parse_stack.top() == start_tag) {
            parse_stack.pop();
            ++count;
        }
    }

    return count;
}


int locate_word(string line, string word) {
    return line.find(word);
}


string ripple::get_node(string line, string tag) {
    empty_stack();

    string start_tag = "<" + tag + ">";
    string end_tag = "</" + tag + ">";

    stringstream node_stream(line);

    string word;
    string result;

    for (; node_stream >> word; ) {
        if (word == end_tag && !parse_stack.empty()) {
            while (parse_stack.top() != start_tag) {
                result = result.insert(0, " " + parse_stack.top());
                parse_stack.pop();
            }
            result = result.insert(0, " " + parse_stack.top());
            parse_stack.pop();
        } else {
            parse_stack.push(word);
        }

    }

    return ripple::trim(result + " " + end_tag);
}


string ripple::get_node_text(string line, string tag) {
    empty_stack();

    string start_tag = "<" + tag + ">";
    string end_tag = "</" + tag + ">";

    stringstream node_stream(line);

    string word;
    string result;

    for (; node_stream >> word; ) {
        if (word == end_tag && !parse_stack.empty()) {
            
            while (parse_stack.top() != start_tag) {
                result = result.insert(0, " " + parse_stack.top());
                parse_stack.pop();
            }

            parse_stack.pop();
        } else {
            parse_stack.push(word);
        }
    }

    return trim(result);
}
