#include "file_lib.h"

using namespace std;

bool file_lib::contains_word(string line, string word) {
    return line.find(word) != string::npos ? true : false;
}

int file_lib::length(string line) {
    return line.size();
}

int file_lib::locate_word(string line, string word) {
    return line.find(word);
}

void file_lib::print_line(string line) {
    cout << line << endl;
}
