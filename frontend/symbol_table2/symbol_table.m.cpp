#include "symbol_table.h"

#include <iostream>

using namespace Ripple::symbol_table;

int main(int argc, char *argv[]){

	SymbolTable st;
	st.start_scope();
	st.insert("int", 0, Ripple::AST::t_int);
	st.insert("bool", 1, Ripple::AST::t_bool);
	st.start_scope();
	std::cout << st.contains("int") << std::endl;
	std::cout << st.contains_in_scope("int") << std::endl;
	st.end_scope();
	std::cout << st.contains("int") << std::endl;
	st.end_scope();
	st.insert("sss", 0, Ripple::AST::t_bool);
}