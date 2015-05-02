#ifndef XML_PARSE_TEST_HPP
#define XML_PARSE_TEST_HPP

#include <assert.h>
#include <iostream>
#include <string>

#include "xml_lib.hpp"

using namespace std;

void test_contains_tag(string line);
void test_does_not_contain_tag(string line);
void test_contains_word(string line);
void test_does_not_contain_word(string line);
void test_line_size(string line);

#endif
