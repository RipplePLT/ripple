#ifndef INCLUDED_AST_NODE
#define INCLUDED_AST_NODE

#include <string>
#include <string.h>
#include <iostream>

extern bool error;
extern int line_no;

#ifndef INCLUDED_PARSE_ERRORS
#include "../parse_errors.h"
#endif

namespace Ripple {
namespace AST {

using namespace std;

enum d_base_type {
	t_bool = 0,
	t_int = 1,
	t_double = 2,
	t_string = 3
};
/*
string base_type_to_string(d_base_type base_type){
	switch(base_type){
		case t_bool:
			return "bool";
		case t_int:
			return "int";
		case t_double:
			return "double";
		case t_string:
			return "string";
	}
}*/

enum d_derived_type {
	t_none = 0,
	t_array = 1,
	t_dataset = 2
};
/*
string derived_type_to_string(d_derived_type derived_type){
	switch(derived_type){
		case t_none:
			return "none";
		case t_array:
			return "array";
		case t_dataset:
			return "dataset";
	}
}*/

class ASTNode {
public:
	string code;
	d_base_type base_type;
	d_derived_type derived_type;
};

}
}

#endif