#ifndef __LINKED_VAR_HPP__
#define __LINKED_VAR_HPP__

#include <vector>
#include <unordered_map>
#include "expression_tree.hpp"
#include "link_val.hpp"

using namespace std;

/*
 * The linked_var class represents a single linked variable.
 */
class linked_var {
private:
	link_val value; // Current value
	void *address; // Address of corresponding C++ variable
	ExpressionNode expression; // Linked expression

	void update_cpp_var();
public:
	// Hash map from a memory address to a list of linked_vars
	//   which depend on that memory address.
	static unordered_map<void *, vector<linked_var *>*> references;

	static void register_cpp_var (void *var);
	static void update_nonlinked_var (void *var);
	static void reset_refs ();
	linked_var(void *var, ExpressionNode *exp); // Ctor
	link_val get_value();
	void update(link_val new_value); // Assignment
	void update(); // For testing only
};

#endif
