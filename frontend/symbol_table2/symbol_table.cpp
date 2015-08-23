#ifndef INCLUDED_SYMBOL_TABLE
#include "symbol_table.h"
#endif

namespace Ripple {
namespace symbol_table {

/**
 * SYMBOL TABLE NODE
 */

SymbolTable::SymbolTableNode::SymbolTableNode(){
	parent = sibling = child = nullptr;
};

SymbolTable::SymbolTableNode::~SymbolTableNode(){
	
	delete child;
	SymbolTableNode *n = sibling;
    SymbolTableNode *next;

    while(n) {
        next = n->sibling;
        delete n;
        n = next;
    }

	for(auto it = table.begin(); it != table.end(); ++it){
		delete it->second;
	}
}

void
SymbolTable::SymbolTableNode::insert(const std::string &key, Symbol* symbol){
	table.insert(std::pair<std::string, Symbol*>(key, symbol));
}

Symbol *
SymbolTable::SymbolTableNode::get(const std::string &key){
	if(table.count(key) == 1){
		return table[key];
	} else {
		return nullptr;
	}
}

bool
SymbolTable::SymbolTableNode::contains(const std::string &key){
	return (table.count(key) == 1);
}

/**
 * SYMBOL TABLE
 */

void 
SymbolTable::insert(const std::string &key,
					int _line_no, 
					AST::d_base_type _base_type,
					AST::d_derived_type _derived_type){

	Symbol *s = new Symbol(key, _line_no, _base_type, _derived_type);
	current->insert(key, s);
}


Symbol *
SymbolTable::get(const std::string &key){
	return current->get(key);
}


bool 
SymbolTable::contains(const std::string &key){
	return current->contains(key);
}


bool
SymbolTable::contains_in_scope(const std::string &key){
	SymbolTableNode *curr = this->current;
	while(curr != nullptr){
		if(curr->contains(key)){
			return true;
		}
		curr = curr->parent;
	}

	return false;
}

void
SymbolTable::start_scope(){
	SymbolTableNode *node = new SymbolTableNode();
	node->sibling = current->child;
	node->parent = current;
	current->child = node;
	current = node;
}

void
SymbolTable::end_scope(){
	current = current->parent;
}

}
}