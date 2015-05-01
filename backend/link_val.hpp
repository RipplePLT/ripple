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
};

#endif
