#include "html_lib.h"

using namespace std;

static stack<string> parse_stack;

static void empty_stack() {

    while (!parse_stack.empty()) {
        parse_stack.pop();
    }
}

string ripple::trim(string line) {
    int index = line.find_first_not_of(" ");
    return line.substr(index);
}

bool ripple::contains_tag(string line, string tag) {
    return line.find(tag) != string::npos ? true : false;
}

int ripple::get_num_tags(string line, string tag) {
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

int ripple::size(string line) {
    return line.size();
}

string ripple::get_body(string line) {
    string body_open_tag = "<body>";
    string body_close_tag = "</body>";

    int start_index = line.find(body_open_tag);
    int end_index = line.find(body_close_tag) + body_close_tag.size();
    int body_size = end_index - start_index;

    string result = line.substr(start_index, body_size);
    return result;
}

string ripple::get_head(string line) {
    string head_open_tag = "<head>";
    string head_close_tag = "</head>";

    int start_index = line.find(head_open_tag);
    int end_index = line.find(head_close_tag) + head_close_tag.size();
    int head_size = end_index - start_index;

    string result = line.substr(start_index, head_size);
    return result;
}

string ripple::get_tag(string line, string tag) {
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

    return trim(result + " " + end_tag);
}
