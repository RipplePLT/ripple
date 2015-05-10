#ifndef __LINK_VAL_H__
#define __LINK_VAL_H__

#include <cmath>
#include <iostream>
#include <stdio.h>
#include <string.h>

/*
 * The link_val class represents a linked variable's value and its
 * type, so that we can deal with dynamic types.
 */

using namespace std;

enum link_val_type {
	ltINT,
	ltINT_PTR,
	ltDOUBLE,
	ltDOUBLE_PTR,
	ltBOOL,
	ltBOOL_PTR,
	ltSTR,
	ltSTR_PTR,
	ltNONE
};

class link_val {
public:
	enum link_val_type type;
	union {
		int intval;
		double doubleval;
		bool boolval;
		string *strval;
		void *ptr;
	} value;

	static bool is_bool_op(const char *op);
	static link_val integer_op(link_val a, link_val b, const char *op);
	static link_val integer_op(link_val a, const char *op);
	static link_val double_op(link_val a, link_val b, const char *op);
	static link_val double_op(link_val a, const char *op);
	static link_val bool_op(link_val a, link_val b, const char *op);
	static link_val bool_op(link_val a, const char *op);
	static link_val str_op(link_val a, link_val b, const char *op);
	int get_int_val() const;
	double get_double_val() const;
	bool get_bool_val() const;
	string get_str_val() const;
	link_val size_node();
	link_val operator+(const link_val &other) const;
	link_val operator-(const link_val &other) const;
	link_val operator*(const link_val &other) const;
	link_val operator/(const link_val &other) const;
	link_val operator^(const link_val &other) const;
	link_val operator>(const link_val &other) const;
	link_val operator<(const link_val &other) const;
	link_val operator>=(const link_val &other) const;
	link_val operator<=(const link_val &other) const;
	link_val operator==(const link_val &other) const;
	link_val operator!=(const link_val &other) const;
	link_val operator&&(const link_val &other) const;
	link_val operator||(const link_val &other) const;
	link_val operator!() const;
	link_val operator-() const;

private:
	// static int integer_op(int a, int b, const char *op);
	template <typename T>
		static T generic_op(T a, T b, const char *op);
	template <typename T> static T generic_op(T a, const char *op);
	static link_val link_val_op(link_val a, link_val b, const char *op);
	static link_val link_val_op(link_val a, const char *op);
};

#endif
