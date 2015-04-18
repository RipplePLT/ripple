#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

#include <cstdio>
#include "hashmap.h"

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
    
    bool put(string word, string v);
    bool put(string word, long v);
    bool put(string word, double v);
    bool put(string word, bool v);
    bool put(string word, char v);

    bool contains(string word);
    
    Entry *get(string word);
};
#endif
