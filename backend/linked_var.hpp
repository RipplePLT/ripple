#ifndef __LINKED_VAR_HPP__
#define __LINKED_VAR_HPP__

#include <list>
// #include "variable_tree.hpp"
#include "../frontend/ast.h"

/*
 * The Linked_Var class represents a single linked variable.
 * For now it supports only integer values.
 * But it will be templatized in due time.
 */

class Linked_Var {
private:
	int value;
	ExpressionNode expression; // Linked expression
	list<Linked_Var*> references; // Linked_Vars to update
public:
	Linked_Var(int *var, ExpressionNode exp);
	int get_value();
	int update_value();
	void add_reference(Linked_Var *var);
};

#endif
