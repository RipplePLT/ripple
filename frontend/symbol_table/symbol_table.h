#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include <cstdio>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

#include "hashmap.h"
#include "../../structures/enum.h"

#define RPL_STD_OUTPUT_FUNCTION "print"
#define RPL_STD_INPUT_FUNCTION "input"
#define RPL_STD_OPEN_FUNCTION "open"
#define RPL_STD_CLOSE_FUNCTION "close"
#define RPL_STD_READ_FUNCTION "read"

#define NUMBER_RESERVED_WORDS 10

#define RPL_STD_OUTPUT_FUNCTION "print"
#define RPL_STD_INPUT_FUNCTION "input"
#define RPL_STD_OPEN_FUNCTION "open"
#define RPL_STD_CLOSE_FUNCTION "close"
#define RPL_STD_READ_FUNCTION "read"

using namespace std;

class SymbolTableNode {
public:
    HashMap *hashmap;
    string name;
    SymbolTableNode *sibling;
    SymbolTableNode *child;
    SymbolTableNode *parent;

    SymbolTableNode();
    SymbolTableNode(string n);
    e_type get_type(string n);
    ~SymbolTableNode();
};


class SymbolTable {
    SymbolTableNode *start;
    SymbolTableNode *current;

    void insert_standard_functions();

public:
    SymbolTable();
    ~SymbolTable();
    void scope_in(int line_no);
    void scope_out(int line_no);

    void new_dataset(int line_no, string name);
    SymbolTableNode *get_dataset(string name);
    Entry *get_dataset_member(string c, string i);

    bool put(string word, e_type type, int line_no, e_symbol_type s);

    bool contains(string word);
    bool contains_in_scope(string word);

    bool add_array(string name, e_type type, int line_no, int arr_length);
    void add_length(string word, int i);
    bool add_function(string name, e_type type, int line_no, list<e_type> *l);
    bool instantiate_dataset(string name, string ds_name, int line_no);
    void add_args(string word, list<e_type> *l);
    void add_dsname(string word, string ds_name);
    void classify(string word, e_symbol_type s);

    Entry *get(string word);
};

#endif
