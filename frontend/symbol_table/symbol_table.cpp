#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "symbol_table.h"


SymbolTableNode::SymbolTableNode() {
    hashmap = new HashMap();
    hashmap->put("print", tINT, 0);
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
    start = nullptr; 
    current = nullptr;
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

bool SymbolTable::put(string word, e_type v, int line_no) {
    return current->hashmap->put(word, v, line_no);
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

Entry *SymbolTable::get(string word) {
    return current->hashmap->get(word);
}

SymbolTable::~SymbolTable() {
    delete start;
}

