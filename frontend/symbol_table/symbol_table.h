#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

#include <cstdio>
#include "hashmap.h"
#include "../../structures/enum.h"

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
    void insert_reserved_words();

    public:
    SymbolTable();
    ~SymbolTable();
    void scope_in(int line_no);
    void scope_out(int line_no);
    
    bool put(string word, e_type type, int line_no, e_symbol_type s);

    bool contains(string word);
    bool contains_in_scope(string word);

    void classify(string word, e_symbol_type s);

    Entry *get(string word);
};
#endif
