#include "xml_parse_test.hpp"

using namespace std;

int main() {

    // Set up
    string test_line = "<Book>\n\t<Title>Moby Dick</Title>\n\t<Author>Herman " \
                        "Melville</Author>\n<Book>";

    // Test contains_tag method
    cout << "xml_lib::contains_tag() Tests" << endl;
    cout << "======================================================" << endl;

    test_contains_tag(test_line);
    cout << "test_contains_tag passed!" << endl;

    test_does_not_contain_tag(test_line);
    cout << "test_does_not_contain_tag passed!" << endl;
    cout << endl;
    
    // Test contains_word method
    cout << "xml_lib::contains_word() Tests" << endl;
    cout << "======================================================" << endl;

    test_contains_word(test_line);
    cout << "test_contains_word passed!" << endl;

    test_does_not_contain_word(test_line);
    cout << "test_does_not_contain_word passed!" << endl;
    cout << endl;

    return 0;
}

void test_contains_tag(string line) {
    bool contains = xml_lib::contains_tag(line, "<Title>");
    assert(contains == true);
}

void test_does_not_contain_tag(string line) {
    bool contains = xml_lib::contains_tag(line, "<Dog>");
    assert(contains == false);
}

void test_contains_word(string line) {
    bool contains = xml_lib::contains_word(line, "Herman");
    assert(contains == true);
}

void test_does_not_contain_word(string line) {
    bool contains = xml_lib::contains_word(line, "Doge");
    assert(contains == false);
}
