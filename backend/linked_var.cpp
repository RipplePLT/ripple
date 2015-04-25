// #include "variable_tree.hpp"
#include "linked_var.hpp"

Linked_Var::Linked_Var(int *var, ExpressionNode exp) {
	this->expression = exp;
	// this->value = exp.evaluate().value.i;
}

int Linked_Var::get_value() {
    return this->value;
}

int Linked_Var::update_value() {
	// this->value = this->expression.evaluate().value.i;
	return this->value;
}

void Linked_Var::add_reference(Linked_Var *var) {
	references.push_front(var);
}
