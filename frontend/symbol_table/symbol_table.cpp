#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "symbol_table.h"

SymbolTableNode::SymbolTableNode() {
    name = "";
    hashmap = new HashMap();
    sibling = nullptr;
    child = nullptr;
    parent = nullptr;
}

SymbolTableNode::SymbolTableNode(string n) {
    name = n;
    hashmap = new HashMap();
    sibling = nullptr;
    child = nullptr;
    parent = nullptr;
}

e_type SymbolTableNode::get_type(string n) {
    Entry *found;
    if ((found = hashmap->get(n)))
        return found->type;
    else
        return tNOTYPE;
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
    insert_standard_functions();
}

void SymbolTable::insert_standard_functions() {
    /* Print */
    add_function(RPL_STD_OUTPUT_FUNCTION, tVOID, 0, nullptr);
    
    /* Files */
    add_function("contains_word", tBOOL, 0,  new list<e_type>({ tSTRING, tSTRING }));  
    add_function("length", tINT, 0, new list<e_type>({ tSTRING }));
    add_function("print_line", tVOID, 0, new list<e_type>({ tSTRING }));
    add_function("locate_word", tINT, 0, new list<e_type>({ tSTRING, tSTRING }));

    /* HTML */
    add_function("contains_tag", tBOOL, 0, new list<e_type>({ tSTRING, tSTRING }));
    add_function("get_num_tags", tINT, 0, new list<e_type>({ tSTRING, tSTRING }));
    add_function("size", tINT, 0, new list<e_type>({ tSTRING }));
    add_function("get_body", tSTRING, 0, new list<e_type>({ tSTRING }));
    add_function("get_head", tSTRING, 0, new list<e_type>({ tSTRING }));
    add_function("get_tag", tSTRING, 0, new list<e_type>({ tSTRING, tSTRING }));
    

    /* XML */
    add_function("get_num_nodes", tINT, 0, new list<e_type>({ tSTRING, tSTRING }));
    add_function("get_node", tINT, 0, new list<e_type>({ tSTRING, tSTRING }));
    add_function("get_node_text", tINT, 0, new list<e_type>({ tSTRING, tSTRING }));
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

    SymbolTableNode *node = new SymbolTableNode(); 

    current->sibling = node;
    current = node;
}

bool SymbolTable::add_function(string name, e_type type, int line_no, list<e_type> *args) {
    bool error = false;
    if (contains_in_scope(name)) {
        cout << "Redefinition of function " << name << " previously defined on line " << line_no << endl;
        error = true;
    } else {
        put(name, type, line_no, tFUNC);
        add_args(name, args);
    }
    return error;
}

bool SymbolTable::add_array(string name, e_type type, int line_no, int length) {
    bool error = false;
    if (contains_in_scope(name)) {
        error = true;
    } else {
        put(name, type, line_no, tARR);
        add_length(name, length);
    }
    return error;
}

bool SymbolTable::instantiate_dataset(string instance_name, string ds_name, int line_no) {
    bool error = false;
    if (contains_in_scope(instance_name) && get(instance_name)->type != tNOTYPE) {
        error = true;
    } else {
        add_dsname(instance_name, ds_name);
    }
    return error;
}

void SymbolTable::add_dsname(string name, string ds_name) {
    Entry *entry = get(name);
    entry->ds_name = ds_name;
    entry->type = tDERIV;
}

void SymbolTable::new_dataset(int line_no, string name) {
    SymbolTableNode *node = new SymbolTableNode(name);

    node->parent = current;
    node->sibling = current->child;
    current->child = node;
    current = node;
}

SymbolTableNode *SymbolTable::get_dataset(string name) {
    SymbolTableNode *node;
    for(node = current; node; node = node->sibling) {
        if (!node->name.empty() && node->name.compare(name) == 0) {
            return node;
        }
    }
    return nullptr;
}

Entry *SymbolTable::get_dataset_member(string name, string member_name) {
    SymbolTableNode *node = get_dataset(name);
    return node->hashmap->get(member_name);
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

void SymbolTable::add_length(string word, int l) {
    get(word)->add_length(l);
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
}
