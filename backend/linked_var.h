#ifndef __LINKED_VAR_H__
#define __LINKED_VAR_H__

#include <vector>
#include <unordered_map>
#include "expression_tree.h"
#include "link_val.h"

using namespace std;

union aux_fn {
	void (*int_fn)(int);
	void (*double_fn)(double);
	void (*bool_fn)(bool);
	void (*str_fn)(string *);
};

/*
 * The linked_var class represents a single linked variable.
 */
class linked_var {
private:
	link_val value; // Current value
	void *address; // Address of corresponding C++ variable
	ExpressionNode expression; // Linked expression
	union aux_fn aux; // Auxiliary function

	void update_cpp_var();
	void call_aux(void *arg);
public:
	// Hash map from a memory address to a list of linked_vars
	//   which depend on that memory address.
	static unordered_map<void *, vector<linked_var *>*> references;

	bool has_aux;
	static void register_cpp_var (void *var);
	static void update_nonlinked_var (void *var);
	static void reset_refs ();
	linked_var(void *var, ExpressionNode *exp); // Ctor
	link_val get_value();
	void update(link_val new_value); // Assignment
	void update(); // For testing only
	void assign_aux_fn(void *fn);
};

#endif
