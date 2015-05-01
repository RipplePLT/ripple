#ifndef __LINK_VAL_HPP__
#define __LINK_VAL_HPP__

/*
 * The link_val class represents a linked variable's value and its
 * type, so that we can deal with dynamic types.
 */

enum link_val_type {
	ltINT,
	ltINT_PTR,
	ltFLOAT,
	ltFLOAT_PTR,
	ltNONE
};

class link_val {
public:
	enum link_val_type type;
	union {
		int intval;
		float floatval;
		void *ptr;
	} value;

	static link_val integer_op(link_val a, link_val b, const char *op);
	static link_val float_op(link_val a, link_val b, const char *op);
	int get_int_val() const;
	float get_float_val() const;
	link_val operator+(const link_val &other) const;
	link_val operator-(const link_val &other) const;
	link_val operator*(const link_val &other) const;
	link_val operator/(const link_val &other) const;
	link_val operator^(const link_val &other) const;

private:
	static int integer_op(int a, int b, const char *op);
};

#endif
