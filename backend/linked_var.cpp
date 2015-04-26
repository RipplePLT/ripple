#include <iostream>
#include <vector>
#include <unordered_map>
#include "variable_tree.hpp"
#include "linked_var.hpp"

unordered_map<void *, vector<Linked_Var*>> Linked_Var::references;

Linked_Var::Linked_Var(int *var, ExpressionNode exp) {
	this->address = var;
	this->expression = exp;
	this->value = exp.evaluate();
	*(int *)(this->address) = this->value.value.intval;
}

struct link_val Linked_Var::get_value() {
    return this->value;
}

void Linked_Var::update() {
	int i;
	this->value = this->expression.evaluate();
	// THIS IS NOT THE RIGHT VALUE
	*(int *)(this->address) = this->value.value.intval;
	cout << "x has been changed to the wrong value" << endl;
	// Recursively update children
	// for (i = 0; i < references[this->address].size(); i++)
	//	references[this->address][i]->update();
}
void Linked_Var::update(struct link_val new_value) {
	this->value = new_value;
	*(int *)(this->address) = new_value.value.intval;
	// @TODO iterate through refs and update() them
}
