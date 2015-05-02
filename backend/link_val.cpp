#include <cmath>
#include <string.h>
#include <stdio.h>
#include "link_val.hpp"

int link_val::get_int_val() const {
	return (type == ltINT) ? value.intval :
		(type == ltINT_PTR) ? *(int *)value.ptr:
		0; // should never happen
}

double link_val::get_double_val() const {
	return (type == ltDOUBLE) ? value.doubleval :
		(type == ltINT) ? value.intval :
		(type == ltINT_PTR) ? *(int *)value.ptr :
		(type == ltDOUBLE_PTR) ? *(double *)value.ptr:
		0;
}

template <typename T>
T link_val::generic_op(T a, T b, const char *op) {
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

link_val link_val::link_val_op(link_val a, link_val b, const char *op) {
	if (a.type == ltDOUBLE || b.type == ltDOUBLE ||
			a.type == ltDOUBLE_PTR || b.type == ltDOUBLE_PTR)
		return double_op(a, b, op);
	else
		return integer_op(a, b, op);
}

link_val link_val::integer_op(link_val a, link_val b, const char *op) {
	int a_int, b_int;
	link_val *result = new link_val();

	a_int = a.get_int_val();
	b_int = b.get_int_val();

	result->type = ltINT;
	result->value.intval = generic_op<int>(a_int, b_int, op);
	return *result;
}

link_val link_val::double_op(link_val a, link_val b, const char *op) {
	double a_double, b_double;
	link_val *result = new link_val();

	a_double = a.get_double_val();
	b_double = b.get_double_val();

	result->type = ltDOUBLE;
	result->value.doubleval = generic_op<double>(a_double, b_double, op);
	return *result;
}

link_val link_val::operator+(const link_val &other) const {
	return link_val_op(*this, other, "+");
}

link_val link_val::operator-(const link_val &other) const {
	return link_val_op(*this, other, "-");
}

link_val link_val::operator*(const link_val &other) const {
	return link_val_op(*this, other, "*");
}

link_val link_val::operator/(const link_val &other) const {
	return link_val_op(*this, other, "/");
}

link_val link_val::operator^(const link_val &other) const {
	return link_val_op(*this, other, "^");
}
