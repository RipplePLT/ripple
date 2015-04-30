#include <iostream>
#include <vector>
#include <unordered_map>
#include "expression_tree.hpp"
#include "linked_var.hpp"

/*
 * Global hash map from memory address to list of linked_vars
 * which reference that memory address.
 */
unordered_map<void *, vector<linked_var *>> linked_var::references;

/*
 * Creates a linked_var object, which represents a linked variable.
 * It takes a pointer to the corresponding C++ variable, and the
 * link expression represented as an ExpressionNode.
 */
linked_var::linked_var(int *var, ExpressionNode *exp) {
	// Assign member values
	this->address = var;
	this->expression = *exp;
	this->value = exp->evaluate();

	// Set the corresponding C++ variable to the proper value.
	switch (this->value.type) {
	case (ltINT):
		*(int *)(this->address) = this->value.value.intval;
		break;
	case (ltINT_PTR): 
		*(int *)(this->address) = *(int *)this->value.value.ptr;
		break;
	default:
		break;
	}
}

struct link_val linked_var::get_value() {
    return this->value;
}

/*
 * Update the value of a linked variable, and all the linked
 * variables that depend on it, based on the present values  of the
 * relevant C++ variables, at least one of which presumably has
 * changed.
 *
 * This implementation will not be used, because it would create a
 * race condition.
 */
void linked_var::update() {
	int i;
	this->value = this->expression.evaluate();
	*(int *)(this->address) =
		BinaryExpressionNode::get_int_val(this->value);

	// Recursively update children
	for (i = 0; i < references[this->address].size(); i++)
		references[this->address][i]->update();
}

/*
 * Set the present linked_var to the given value, then accordingly
 * update all linked_vars which depend on this one.
 */
void linked_var::update(struct link_val new_value) {
	int i;
	this->value = new_value;
	*(int *)(this->address) =
		BinaryExpressionNode::get_int_val(this->value);

	// Recursively update children
	for (i = 0; i < references[this->address].size(); i++)
		references[this->address][i]->update();
}
