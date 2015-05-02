#include "html_lib.hpp"

using namespace std;

static stack<string> parse_stack;

static void empty_stack() {

    while (!parse_stack.empty()) {
        parse_stack.pop();
    }
}

bool html_lib::contains_tag(string line, string tag) {
    return line.find(tag) > 0 ? true : false;
}

bool html_lib::contains_word(string line, string word) {
    return line.find(word) > 0 ? true: false;
}

string html_lib::get_body(string line) {
    string body_open_tag = "<body>";
    string body_close_tag = "</body>";

    int start_index = line.find(body_open_tag);
    int end_index = line.find(body_close_tag) + body_close_tag.size();
    int body_size = end_index - start_index;

    string result = line.substr(start_index, body_size);
    return result;
}

vector<string> html_lib::get_collection(string line, string tag) {
    empty_stack();
    vector<string> nodes;
    return nodes;
}

string html_lib::get_head(string line) {
    string head_open_tag = "<head>";
    string head_close_tag = "</head>";

    int start_index = line.find(head_open_tag);
    int end_index = line.find(head_close_tag) + head_close_tag.size();
    int head_size = end_index - start_index;

    string result = line.substr(start_index, head_size);
    return result;
}

int html_lib::get_num_tags(string line, string tag) {
    empty_stack();
    int count = 0;
    return count;
}

string html_lib::get_tag(string line, string tag) {
    empty_stack();
    return "";
}

int html_lib::size(string line) {
    return line.size();
}
