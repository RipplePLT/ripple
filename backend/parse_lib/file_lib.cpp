#include "file_lib.h"

using namespace std;


bool ripple::contains_word(string line, string word) {
    return line.find(word) != string::npos ? true : false;
}


int ripple::length(string line) {
    return line.size();
}


int ripple::locate_word(string line, string word) {
    return line.find(word);
}


void ripple::print_line(string line) {
    cout << line << endl;
}
