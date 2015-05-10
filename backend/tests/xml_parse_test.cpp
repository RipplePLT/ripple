#include "xml_parse_test.h"

using namespace std;

/**
 * Small test suite to check the functionality of the xml parsing library.
 *
 * Author: Alexander Roth
 **/
int main() {

    // Set up
    string test_line = "<Book>\n\t<Title> Moby Dick </Title>\n\t<Author>" \
                       " Herman Melville </Author>\n<Book>";
    string test_lines = "<Root>\n\t<Books>\n\t\t<Title> Test 1 </Title>\n" \
                        "\t\t<Title> Test 2 </Title>\n\t</Books>\n</Root>";

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

    // Test get_collection method
    cout << "xml_lib::get_collection() Test" << endl;
    cout << "======================================================" << endl;

    test_get_collection(test_line);
    cout << "test_get_collection passed!" << endl;
    cout << endl;

    // Test get_node method
    cout << "xml_lib::get_node() Test" << endl;
    cout << "======================================================" << endl;

    test_get_node(test_line);
    cout << "test_get_node passed!" << endl;
    cout << endl;

    // Test get_node_text method
    cout << "xml_lib::get_node_text() Test" << endl;
    cout << "======================================================" << endl;

    test_get_node_text(test_line);
    cout << "test_get_node_text passed!" << endl;
    cout << endl;


    // Test get_num_nodes method
    cout << "xml_lib::get_num_nodes() Test" << endl;
    cout << "======================================================" << endl;

    test_get_num_nodes(test_line);
    cout << "test_get_num_nodes passed!" << endl;
    cout << endl;

    // Test size method
    cout << "xml_lib::size() Test" << endl;
    cout << "======================================================" << endl;
    test_line_size(test_line);
    test_line_size(test_lines);
    cout << "test_line_size passed!" << endl;
    cout << endl;

    cout << test_lines << endl;
    return 0;
}

void test_contains_tag(string line) {
    bool contains = xml_lib::contains_tag(line, "<Title>");
    assert(contains == true);
}

void test_contains_word(string line) {
    bool contains = xml_lib::contains_word(line, "Herman");
    assert(contains == true);
}

void test_does_not_contain_tag(string line) {
    bool contains = xml_lib::contains_tag(line, "<Dog>");
    assert(contains == false);
}

void test_does_not_contain_word(string line) {
    bool contains = xml_lib::contains_word(line, "Doge");
    assert(contains == false);
}

void test_get_collection(string line) {
    vector<string> nodes = xml_lib::get_collection(line, "Author");
    assert(nodes.size() == 1);
    assert(nodes[0] == "Herman Melville");
}

void test_get_node(string line) {
    string author = xml_lib::get_node(line, "Author");
    assert(author == "<Author> Herman Melville </Author>");
}

void test_get_node_text(string line) {
    string text = xml_lib::get_node_text(line, "Title");
    assert(text == "Moby Dick");
}

void test_get_num_nodes(string line) {
    int count = xml_lib::get_num_nodes(line, "Author");
    assert(count == 1);
}

void test_line_size(string line) {
    int check = line.size();
    int len = xml_lib::size(line);
    assert(check == len);
}
