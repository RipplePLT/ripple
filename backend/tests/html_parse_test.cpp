#include "html_parse_test.hpp"

int main() {

    // Setup
    string test_line = "<html>\n\t<head>Some text</head>\n</html>";
    
    // Test contains_tag method
    cout << "html_lib::contains_tag() Tests" << endl;
    cout << "======================================================" << endl;
    
    test_contains_tag(test_line);
    cout << "test_contains_tag passed!" << endl;
    cout << endl;

    test_does_not_contain_tag(test_line);
    cout << "test_does_not_contain_tag passed!" << endl;

    // Test contains_word method
    cout << "html_lib::contains_word() Tests" << endl;
    cout << "======================================================" << endl;

    test_contains_word(test_line);
    cout << "test_contains_word passed!" << endl;

    test_does_not_contain_word(test_line);
    cout << "test_does_not_contain_word passed!" << endl;
    cout << endl;

    return 0;
}

void test_contains_tag(string line) {
    bool contains = html_lib::contains_tag(line, "<head>");
    assert(contains == true);
}

void test_does_not_contain_tag(string line) {
    bool contains = html_lib::contains_tag(line, "<test>");
    assert(contains == false);
}

void test_contains_word(string line) {
    bool contains = html_lib::contains_word(line, "text");
    assert(contains == true);
}

void test_does_not_contain_word(string line) {
    bool contains = html_lib::contains_word(line, "dog");
    assert(contains == false);
}

void test_get_body(string line) {
}

void test_get_collection(string line) {
}

void test_get_head(string line) {
}

void test_size(string line) {
}
