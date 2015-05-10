#include <cmath>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "link_val.hpp"

bool link_val::is_bool_op(const char *op) {
	return (!strcmp(op, ">") ||
		!strcmp(op, "<") ||
		!strcmp(op, ">=") ||
		!strcmp(op, "<=") ||
		!strcmp(op, "==") ||
		!strcmp(op, "!="));
}

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

bool link_val::get_bool_val() const {
	return (type == ltDOUBLE) ? !!value.doubleval :
		(type == ltINT) ? !!value.intval :
		(type == ltBOOL) ? value.boolval :
		(type == ltINT_PTR) ? !!*(int *)value.ptr :
		(type == ltDOUBLE_PTR) ? !!*(double *)value.ptr :
		(type == ltBOOL_PTR) ? *(bool *)value.ptr:
		0;
}

string link_val::get_str_val() const {
	switch(type) {
	case (ltINT) :
		return to_string(value.intval);
		break;
	case (ltINT_PTR) :
		return to_string(*(int *)value.ptr);
		break;
	case (ltSTR) :
		return *value.strval;
		break;
	case (ltSTR_PTR) :
		return **(string **)value.ptr;
		break;
	case (ltDOUBLE) :
		return to_string(value.doubleval);
		break;
	case (ltDOUBLE_PTR) :
		return to_string(*(double *)value.ptr);
		break;
	case (ltBOOL) :
		return to_string(value.boolval);
		break;
	case (ltBOOL_PTR) :
		return to_string(*(bool *)value.ptr);
		break;
	default:
		return NULL;
	}
}

link_val link_val::size_node() {
	link_val *result = new link_val();
	result->type = ltINT;
	result->value.intval = 
		(type == ltINT) ? sizeof(int) :
		(type == ltDOUBLE) ? sizeof(double) :
		(type == ltBOOL) ? sizeof(bool) :
		(type == ltINT_PTR) ? sizeof(void *) :
		(type == ltDOUBLE_PTR) ? sizeof(void *) :
		(type == ltBOOL_PTR) ? sizeof(void *) :
		0;

	return *result;
}

template <typename T>
T link_val::generic_op(T a, const char *op) {
	if (!strcmp(op, "!"))
		return !a;
	else
		return 0;
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
	else if (!strcmp(op, "//"))
		return a / b; // @TODO
	else if (!strcmp(op, "^"))
		return (T)pow(a, b);
	else if (!strcmp(op, ">"))
		return a > b;
	else if (!strcmp(op, "<"))
		return a < b;
	else if (!strcmp(op, ">="))
		return a >= b;
	else if (!strcmp(op, "<="))
		return a <= b;
	else if (!strcmp(op, "=="))
		return a == b;
	else if (!strcmp(op, "!="))
		return a != b;
	else if (!strcmp(op, "&&"))
		return a && b;
	else if (!strcmp(op, "||"))
		return a || b;
	else
		return 0;
}

link_val link_val::link_val_op(link_val a, link_val b, const char *op) {
	if (a.type == ltSTR || b.type == ltSTR ||
			a.type == ltSTR_PTR || b.type == ltSTR_PTR)
		return str_op(a, b, op);
	if (a.type == ltBOOL || b.type == ltBOOL ||
			a.type == ltBOOL_PTR || b.type == ltBOOL_PTR)
		return bool_op(a, b, op);
	if (a.type == ltDOUBLE || b.type == ltDOUBLE ||
			a.type == ltDOUBLE_PTR || b.type == ltDOUBLE_PTR)
		return double_op(a, b, op);
	return integer_op(a, b, op);
}

link_val link_val::link_val_op(link_val a, const char *op) {
	if (a.type == ltINT || a.type == ltINT_PTR)
		return integer_op(a, op);
	else if (a.type == ltDOUBLE || a.type == ltDOUBLE_PTR)
		return double_op(a, op);
	return bool_op(a, op); // logical not
}

link_val link_val::str_op(link_val a, link_val b, const char *op) {
	string a_str, b_str;
	link_val *result = new link_val();

	a_str = a.get_str_val();
	b_str = b.get_str_val();
	
	result->type = ltSTR;

	if (!strcmp(op, "+")) {
		string *temp = new string(a_str + b_str);
		result->value.strval = temp;
	}

	return *result;
}

link_val link_val::integer_op(link_val a, link_val b, const char *op) {
	int a_int, b_int;
	link_val *result = new link_val();

	a_int = a.get_int_val();
	b_int = b.get_int_val();

	if (is_bool_op(op)) {
		result->type = ltBOOL;
		result->value.boolval = generic_op<int>(a_int, b_int, op);
	} else {
		result->type = ltINT;
		result->value.intval = generic_op<int>(a_int, b_int, op);
	}

	return *result;
}

link_val link_val::integer_op(link_val a, const char *op) {
	// Currently only includes negation
	int a_int;
	link_val *result = new link_val();

	a_int = a.get_int_val();

	result->type = ltINT;
	result->value.intval = -a_int;

	return *result;
}

link_val link_val::double_op(link_val a, link_val b, const char *op) {
	double a_double, b_double;
	link_val *result = new link_val();

	a_double = a.get_double_val();
	b_double = b.get_double_val();

	if (is_bool_op(op)) {
		result->type = ltBOOL;
		result->value.boolval = generic_op<double>(a_double, b_double, op);
	} else {
		result->type = ltDOUBLE;
		result->value.doubleval = generic_op<double>(a_double, b_double, op);
	}

	return *result;
}

link_val link_val::double_op(link_val a, const char *op) {
	// Currently only negation
	double a_double;
	link_val *result = new link_val();

	a_double = a.get_double_val();

	result->type = ltDOUBLE;
	result->value.doubleval = -a_double;

	return *result;
}

link_val link_val::bool_op(link_val a, link_val b, const char *op) {
	bool a_bool, b_bool;
	link_val *result = new link_val();

	a_bool = a.get_bool_val();
	b_bool = b.get_bool_val();

	result->type = ltBOOL;
	result->value.boolval = generic_op<bool>(a_bool, b_bool, op);

	return *result;
}

link_val link_val::bool_op(link_val a, const char *op) {
	bool a_bool;
	link_val *result = new link_val();

	a_bool = a.get_bool_val();

	result->type = ltBOOL;
	result->value.boolval = generic_op<bool>(a_bool, op);

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

link_val link_val::operator>(const link_val &other) const {
	return link_val_op(*this, other, ">");
}

link_val link_val::operator<(const link_val &other) const {
	return link_val_op(*this, other, "<");
}

link_val link_val::operator>=(const link_val &other) const {
	return link_val_op(*this, other, ">=");
}

link_val link_val::operator<=(const link_val &other) const {
	return link_val_op(*this, other, "<=");
}

link_val link_val::operator==(const link_val &other) const {
	return link_val_op(*this, other, "==");
}

link_val link_val::operator!=(const link_val &other) const {
	return link_val_op(*this, other, "!=");
}

link_val link_val::operator&&(const link_val &other) const {
	return link_val_op(*this, other, "&&");
}

link_val link_val::operator||(const link_val &other) const {
	return link_val_op(*this, other, "||");
}

link_val link_val::operator!() const {
	return link_val_op(*this, "!");
}

link_val link_val::operator-() const {
	return link_val_op(*this, "-");
}
