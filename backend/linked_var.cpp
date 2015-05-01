#include <iostream>
#include <vector>
#include <unordered_map>
#include "expression_tree.hpp"
#include "linked_var.hpp"
#include "link_val.hpp"

/*
 * Global hash map from memory address to list of linked_vars
 * which reference that memory address.
 */
unordered_map<void *, vector<linked_var *>*> linked_var::references;

/*
 * Creates a linked_var object, which represents a linked variable.
 * It takes a pointer to the corresponding C++ variable, and the
 * link expression represented as an ExpressionNode.
 */
linked_var::linked_var(int *var, ExpressionNode *exp) {
	int i;

	// Assign member values
	this->address = var;
	this->expression = *exp;
	this->value = exp->evaluate();

	// Put references into dependency tree
	if (exp->refs != NULL)
		for (i = 0; i < exp->refs->size(); i++)
			references[(*exp->refs)[i]]->push_back(this);

	// Set the corresponding C++ variable to the proper value.
	this->update_cpp_var();
}

link_val linked_var::get_value() {
    return this->value;
}

void linked_var::update_cpp_var() {
	switch (this->value.type) {
	case (ltINT):
		*(int *)(this->address) = this->value.value.intval;
		break;
	case (ltINT_PTR): 
		*(int *)(this->address) = *(int *)this->value.value.ptr;
		break;
	case (ltFLOAT):
		*(float *)(this->address) = this->value.value.floatval;
		break;
	case (ltFLOAT_PTR):
		*(float *)(this->address) = *(float *)this->value.value.ptr;
	default:
		break;
	}
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
	this->update_cpp_var();

	// Recursively update children
	if (references[this->address] != NULL)
		for (i = 0; i < references[this->address]->size(); i++)
			if (references[this->address] != NULL)
				(*references[this->address])[i]->update();
}

/*
 * Set the present linked_var to the given value, then accordingly
 * update all linked_vars which depend on this one.
 */
void linked_var::update(link_val new_value) {
	int i;
	this->value = new_value;
	this->update_cpp_var();

	// Recursively update children
	for (i = 0; i < references[this->address]->size(); i++)
		(*references[this->address])[i]->update();
}
