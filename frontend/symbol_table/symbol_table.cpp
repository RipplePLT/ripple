#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "symbol_table.h"

SymbolTableNode::SymbolTableNode() {
    hashmap = new HashMap();
    sibling = nullptr;
    child = nullptr;
    parent = nullptr;
}

SymbolTableNode::~SymbolTableNode() {
    delete child;

    SymbolTableNode *n = sibling;
    SymbolTableNode *next;

    while(n) {
        next = n->sibling;
        delete n;
        n = next;
    }

    delete hashmap;
}


SymbolTable::SymbolTable(){
    SymbolTableNode *main = new SymbolTableNode();
    start = main; 
    current = main;
    insert_reserved_words();
}

void SymbolTable::scope_in(int line_no) {
    SymbolTableNode *node = new SymbolTableNode;
    if (!start) {
        start = node;
        node->sibling = node->parent = nullptr;
    } else {
        node->parent = current;
        node->sibling = current->child;
        current->child = node;
    }
    current = node;
}

void SymbolTable::scope_out(int line_no) {
    if (current->parent){
        current = current->parent;
        return;
    }

    SymbolTableNode *node = new SymbolTableNode; 

    current->sibling = node;
    current = node;
}

void SymbolTable::insert_reserved_words(){
    for(std::vector<string>::iterator it = reserved.begin(); it != reserved.end(); ++it) {
        put(*it, tVOID, -1, tNOSTYPE);
    }
}

bool SymbolTable::put(string word, e_type v, int line_no, e_symbol_type s = tNOSTYPE) {
    return current->hashmap->put(word, v, line_no, s);
}

void SymbolTable::classify(string word, e_symbol_type s) {
    get(word)->classify(s);
}

void SymbolTable::add_args(string word, list<e_type> *l) {
    get(word)->add_args(l);
}

bool SymbolTable::contains(string word) {
    SymbolTableNode *n = current;
    while(n) {
        if (n->hashmap->contains(word))
            return true;
        n = n->parent;
    }
    return false;
}

bool SymbolTable::contains_in_scope(string word){
    return current->hashmap->contains(word);
}

Entry *SymbolTable::get(string word) {
    
    SymbolTableNode *n = current;
    while(n) {
        if (n->hashmap->contains(word))
            return n->hashmap->get(word);
        n = n->parent;
    }
    return nullptr;
}

SymbolTable::~SymbolTable() {
    //delete start;
}
