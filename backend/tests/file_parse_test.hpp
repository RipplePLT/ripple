#ifndef FILE_PARSE_TEST_HPP
#define FILE_PARSE_TEST_HPP

#include <assert.h>
#include <iostream>
#include <string>

#include "file_lib.hpp"

using namespace std;

void test_contains_word(string line);

void test_does_not_contain_word(string line);

void test_length(string line);
void test_locate_word(string line);

#endif
