#ifndef __LINKEDVAR_HPP__
#define __LINKEDVAR_HPP__

#include <list>
#include "variable_tree.hpp"

/*
 * The LinkedVar class represents a single linked variable.
 * For now it supports only integer values.
 * But it will be templatized in due time.
 */

class LinkedVar {
private:
	int value;
	ExpressionNode expression; // Linked expression
	list<LinkedVar*> references; // LinkedVars to update
public:
	LinkedVar(int *var, ExpressionNode exp);
	int get_value();
	int update_value();
	void add_reference(LinkedVar *var);
};

#endif
