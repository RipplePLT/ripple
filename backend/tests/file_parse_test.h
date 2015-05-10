#ifndef __FILE_PARSE_TEST_H__
#define __FILE_PARSE_TEST_H__

#include <assert.h>
#include <iostream>
#include <string>

#include "file_lib.h"

using namespace std;

void test_contains_word(string line);

void test_does_not_contain_word(string line);

void test_length(string line);
void test_locate_word(string line);

#endif
