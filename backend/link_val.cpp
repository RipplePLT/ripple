#include <cmath>
#include <string.h>
#include "link_val.hpp"

int link_val::get_int_val() const {
	return (type == ltINT) ? value.intval :
		(type == ltINT_PTR) ? *(int *)value.ptr:
		0; // should never happen
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

link_val link_val::operator+(const link_val &other) const {
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
