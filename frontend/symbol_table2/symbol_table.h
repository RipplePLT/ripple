#ifndef INCLUDED_SYMBOL_TABLE
#define INCLUDED_SYMBOL_TABLE

#include <unordered_map>
#include <string>
#include <cstring>
#include "../ast_nodes/ast_node.h"

namespace Ripple {
namespace symbol_table {

class Symbol {
public:
	std::string key;
	int line_no;
	AST::d_base_type base_type;
	AST::d_derived_type derived_type;

	Symbol(std::string _key,
		   int _line_no,
		   AST::d_base_type _base_type,
		   AST::d_derived_type _derived_type)
		: key(_key), line_no(_line_no), base_type(_base_type), derived_type(_derived_type) {};
};

class SymbolTable {
private:
	class SymbolTableNode {
	public:
		SymbolTableNode *parent;
		SymbolTableNode *sibling;
		SymbolTableNode *child;
	private:
		std::unordered_map<std::string, Symbol*> table;
	public:
		SymbolTableNode();
		~SymbolTableNode();
		void insert(const std::string &key, Symbol* symbol);
		Symbol* get(const std::string &key);
		bool contains(const std::string &key);
	};
	SymbolTableNode *first;
	SymbolTableNode *current;

public:

	SymbolTable() { first = current = new SymbolTableNode(); };
	~SymbolTable() { delete first; };

	void insert(const std::string &key, int line_no, AST::d_base_type _base_type, AST::d_derived_type _derived_type = AST::t_none);
	Symbol *get(const std::string &key);
	bool contains(const std::string &key);
	bool contains_in_scope(const std::string &key);

	void start_scope();
	void end_scope();
};

}
}

#endif