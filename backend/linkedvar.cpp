#include "variable_tree.hpp"
#include "linkedvar.hpp"

LinkedVar::LinkedVar(int *var, ExpressionNode exp) {
	this->expression = exp;
	this->value = exp.evaluate().value.i;
}

int LinkedVar::get_value() {
    return this->value;
}

int LinkedVar::update_value() {
	this->value = this->expression.evaluate().value.i;
	return this->value;
}

void LinkedVar::add_reference(LinkedVar *var) {
	references.push_front(var);
}
