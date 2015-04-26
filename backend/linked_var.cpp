#include <iostream>
#include <vector>
#include <unordered_map>
#include "variable_tree.hpp"
#include "linked_var.hpp"

unordered_map<void *, vector<linked_var *>> Linked_Var::references;

linked_var::linked_var(int *var, ExpressionNode exp) {
	this->address = var;
	this->expression = exp;
	this->value = exp.evaluate();
	*(int *)(this->address) = this->value.value.intval;
}

struct link_val linked_var::get_value() {
    return this->value;
}

void linked_var::update() {
	int i;
	this->value = this->expression.evaluate();
	// THIS IS NOT THE RIGHT VALUE
	*(int *)(this->address) = this->value.value.intval;
	cout << "x has been changed to the wrong value" << endl;
	// Recursively update children
	// for (i = 0; i < references[this->address].size(); i++)
	//	references[this->address][i]->update();
}

void linked_var::update(struct link_val new_value) {
	this->value = new_value;
	*(int *)(this->address) = new_value.value.intval;
	// @TODO iterate through refs and update() them
}
