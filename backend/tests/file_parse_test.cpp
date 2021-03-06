#include "file_parse_test.h"

/**
 * Simple test suite for file parse library.
 *
 * Author: Alexander Roth
 **/
int main(int argc, char **argv) {
    // Set up
    string test_line = "Here is a sample string";

    // Test contains_word method
    cout << "ripple::contains_word() Test" << endl;
    cout << "======================================================" << endl;

    test_contains_word(test_line);
    cout << "test_contains_word passed!" << endl;

    test_does_not_contain_word(test_line);
    cout << "test_does_not_contain_word passed!" << endl;
    cout << endl;

    // Test length method
    cout << "ripple::length() Test" << endl;
    cout << "======================================================" << endl;

    test_length(test_line);
    cout << "test_length passed!" << endl;
    cout << endl;

    // Test locate_word method
    // assert(check == local);
    // assert(check == local);
    cout << "ripple::locate_word() Test" << endl;
    cout << "======================================================" << endl;

    test_locate_word(test_line);
    cout << "test_locate_word passed!" << endl;
    cout << endl;

    return 0;
}

void test_contains_word(string line) {
    bool contains = ripple::contains_word(line, "sample");
    assert(contains == true);
}

void test_does_not_contain_word(string line) {
    bool contains = ripple::contains_word(line, "dog");
    assert(contains == false);
}

void test_length(string line) {
    int check = line.size();
    int len = ripple::length(line);
    assert(len == check);
}

void test_locate_word(string line) {
    int local = ripple::locate_word(line, "sample");
    int check = line.find("sample");
    assert(local != string::npos);
    assert(check == local);
}
