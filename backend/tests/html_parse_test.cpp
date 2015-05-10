#include "html_parse_test.h"

/**
 * Small test suite to check the functionality of the html parse library.
 *
 * Author: Alexander Roth
 **/
int main() {

    // Setup
    string test_line = "<html>\n\t<head> Some text </head>\n\t<body> Hello World!"\
                        " </body>\n</html>";
    
    // Test contains_tag method
    cout << "html_lib::contains_tag() Tests" << endl;
    cout << "======================================================" << endl;
    
    test_contains_tag(test_line);
    cout << "test_contains_tag passed!" << endl;

    test_does_not_contain_tag(test_line);
    cout << "test_does_not_contain_tag passed!" << endl;
    cout << endl;

    // Test contains_word method
    cout << "html_lib::contains_word() Tests" << endl;
    cout << "======================================================" << endl;

    test_contains_word(test_line);
    cout << "test_contains_word passed!" << endl;

    test_does_not_contain_word(test_line);
    cout << "test_does_not_contain_word passed!" << endl;
    cout << endl;

    // Test get_body method
    cout << "html_lib::get_body() Tests" << endl;
    cout << "======================================================" << endl;

    test_get_body(test_line);
    cout << "test_get_body passed!" << endl;
    cout << endl;

    // Test get_head method
    cout << "html_lib::get_head() Tests" << endl;
    cout << "======================================================" << endl;

    test_get_head(test_line);
    cout << "test_get_head passed!" << endl;
    cout << endl;

    // Test get_collection method
    cout << "html_lib::get_collection() Test" << endl;
    cout << "======================================================" << endl;

    test_get_collection(test_line);
    cout << "test_get_collection passed!" << endl;
    cout << endl;

    // Test get_num_tags method
    cout << "html_lib::get_num_tags() Test" << endl;
    cout << "======================================================" << endl;

    test_get_num_tags(test_line);
    cout << "test_get_num_tags passed!" << endl;
    cout << endl;

    // Test size method
    cout << "html_lib::size() Tests" << endl;
    cout << "======================================================" << endl;

    test_size(test_line);
    cout << "test_size passed!" << endl;
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
    string body = html_lib::get_body(line);
    assert(body == "<body> Hello World! </body>");
}

void test_get_collection(string line) {
    vector<string> nodes = html_lib::get_collection(line, "body");
    assert(nodes.size() == 1);
}

void test_get_head(string line) {
    string head = html_lib::get_head(line);
    assert(head == "<head> Some text </head>");
}

void test_get_num_tags(string line) {
    int num_tag = html_lib::get_num_tags(line, "body");
    assert(num_tag == 1);
}

void test_get_tag(string line) {
    string tag = html_lib::get_tag(line, "head");
    assert(tag == "<head> Some text </head>");
}

void test_size(string line) {
    int check = line.size();
    int count = html_lib::size(line);
    assert(check == count);
}
