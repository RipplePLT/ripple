#include "xml_lib.hpp"

using namespace std;

static stack<string> parse_stack;

static void empty_stack() {

    while (!parse_stack.empty()) {
        parse_stack.pop();
    }
}

string trim(string line) {
    int index = line.find_first_not_of(" ");
    return line.substr(index);
}

bool xml_lib::contains_tag(string line, string tag) {
    return line.find(tag) != string::npos ? true : false;
}

bool xml_lib::contains_word(string line, string word) {
    return line.find(word) != string::npos ? true : false;
}

int xml_lib::get_num_nodes(string line, string tag) {
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

int xml_lib::size(string line) {
    return line.size();
}
string xml_lib::get_node(string line, string tag) {
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

string xml_lib::get_node_text(string line, string tag) {
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

vector<string> xml_lib::get_collection(string line, string tag) {
    empty_stack();

    string start_tag = "<" + tag + ">";
    string end_tag = "</" + tag + ">";

    string word;
    string result;
    vector<string> nodes;
    stringstream node_stream(line);

    for (; node_stream >> word;) {
        if (word == end_tag && !parse_stack.empty()) {

            while (parse_stack.top() != start_tag) {
                result = result.insert(0, " " + parse_stack.top());
                parse_stack.pop();
            }
            nodes.push_back(trim(result));
            result = "";

            parse_stack.pop();
        } else {
            parse_stack.push(word);
        }
    }

    return nodes;
}

void xml_lib::print_line(string line) {
    cout << line << endl;
}
