#ifndef HTML_PARSE_TEST_HPP
#define HTML_PARSE_TEST_HPP

#include <assert.h>
#include <iostream>
#include <string>

#include "html_lib.hpp"

using namespace std;

void test_contains_tag(string line);
void test_contains_word(string line);

void test_does_not_contain_tag(string line);
void test_does_not_contain_word(string line);

void test_get_body(string line);
void test_get_collection(string line);
void test_get_head(string line);
void test_get_num_tags(string line);
void test_get_tag(string line);

void test_size(string line);

#endif
