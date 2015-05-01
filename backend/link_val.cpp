#include <cmath>
#include <string.h>
#include <stdio.h>
#include "link_val.hpp"

int link_val::get_int_val() const {
	return (type == ltINT) ? value.intval :
		(type == ltINT_PTR) ? *(int *)value.ptr:
		0; // should never happen
}

float link_val::get_float_val() const {
	return (type == ltFLOAT) ? value.floatval :
		(type == ltINT) ? value.intval :
		(type == ltINT_PTR) ? *(int *)value.ptr :
		(type == ltFLOAT_PTR) ? *(float *)value.ptr:
		0;
}

int link_val::integer_op(int a, int b, const char *op) {
	if (!strcmp(op, "+"))
		return a + b;
	else if (!strcmp(op, "-"))
		return a - b;
	else if (!strcmp(op, "*"))
		return a * b;
	else if (!strcmp(op, "/"))
		return a / b;
	else if (!strcmp(op, "^"))
		return pow(a, b);
	else
		return 0;
}

link_val link_val::integer_op(link_val a, link_val b, const char *op) {
	int a_int, b_int;
	link_val *result = new link_val();

	a_int = a.get_int_val();
	b_int = b.get_int_val();

	result->type = ltINT;
	result->value.intval = integer_op(a_int, b_int, op);
	return *result;
}

link_val link_val::float_op(link_val a, link_val b, const char *op) {
	float a_float, b_float;
	link_val *result = new link_val();

	a_float = a.get_float_val();
	b_float = b.get_float_val();

	result->type = ltFLOAT;
	result->value.floatval = a_float + b_float;
	return *result;
}

link_val link_val::operator+(const link_val &other) const {
	if (this->type == ltFLOAT || other.type == ltFLOAT ||
			this->type == ltFLOAT_PTR || other.type == ltFLOAT_PTR)
		return float_op(*this, other, "+");
	else
		return integer_op(*this, other, "+");
}

link_val link_val::operator-(const link_val &other) const {
	return integer_op(*this, other, "-");
}

link_val link_val::operator*(const link_val &other) const {
	return integer_op(*this, other, "*");
}

link_val link_val::operator/(const link_val &other) const {
	return integer_op(*this, other, "/");
}

link_val link_val::operator^(const link_val &other) const {
	return integer_op(*this, other, "^");
}
