#ifndef __LINKED_VAR_HPP__
#define __LINKED_VAR_HPP__

#include <vector>
#include <unordered_map>
#include "variable_tree.hpp"

/*
 * The Linked_Var class represents a single linked variable.
 * For now it supports only integer values.
 * But it will be templatized in due time.
 */

class Linked_Var {
private:
	struct link_val value;
	void *address;
	ExpressionNode expression; // Linked expression
public:
	static unordered_map<void *, vector<Linked_Var*>> references;
	Linked_Var(int *var, ExpressionNode exp);
	struct link_val get_value();
	void update(struct link_val new_value);
	void update();
};

#endif
