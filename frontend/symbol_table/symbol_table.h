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

    public:
    SymbolTable();
    ~SymbolTable();
    void scope_in(int line_no);
    void scope_out(int line_no);
    
    bool put(string word, e_type type, int line_no);

    bool contains(string word);
    
    Entry *get(string word);
};
#endif
