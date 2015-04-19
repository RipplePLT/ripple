#include "../frontend/ast.h"
#include "linkedvar.hpp"

//template<typename T>
//LinkedVar<T>::LinkedVar(T *var, ExpressionNode exp) {
LinkedVar::LinkedVar(int *var, ExpressionNode exp) {
	this->expression = exp;
}

//template<typename T>
//T LinkedVar<T>::get_value() {
int LinkedVar::get_value() {
    return this->value;
}

//template<typename T>
// T LinkedVar<T>::update_value() {
int LinkedVar::update_value() {
	return 0;
}

void LinkedVar::add_reference(LinkedVar *var) {
	references.push_front(var);
}
