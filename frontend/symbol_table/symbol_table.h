#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__

#include <cstdio>
#include <string>
#include <vector>
#include "hashmap.h"
#include "../../structures/enum.h"

#define NUMBER_RESERVED_WORDS 10

using namespace std;

class SymbolTableNode {
    public:
	HashMap *hashmap;
	SymbolTableNode *sibling;
	SymbolTableNode *child;
	SymbolTableNode *parent;

    SymbolTableNode();
    ~SymbolTableNode();
};

class SymbolTable{
    SymbolTableNode *start;
    SymbolTableNode *current;

    std::vector<string> reserved {"if", "else", "for", "while", "link", "byte", "bool", "int", "float", "string", "print"};

    void insert_reserved_words();

    public:
    SymbolTable();
    ~SymbolTable();
    void scope_in(int line_no);
    void scope_out(int line_no);
    
    bool put(string word, e_type type, int line_no, e_symbol_type s);

    bool contains(string word);
    bool contains_in_scope(string word);

    void add_args(string word, list<e_type> *l);
    void classify(string word, e_symbol_type s);

    Entry *get(string word);
};

#endif
