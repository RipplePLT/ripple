#ifndef INCLUDED_LITERAL_NODE
#include "literal_node.h"
#endif

namespace Ripple {
namespace AST {

LiteralNode::LiteralNode(bool _bool){
	d_literal.d_bool = _bool;

	base_type = t_bool;
	derived_type = t_none;

	code = _bool ? "true" : "false";
#ifdef DEBUG
	std::cout << base_type << " " << code << std::endl;
#endif
}

LiteralNode::LiteralNode(int _int){
	d_literal.d_int = _int;

	base_type = t_int;
	derived_type = t_none;

	code = to_string(_int);
#ifdef DEBUG
	std::cout << base_type << " " << code << std::endl;
#endif
}

LiteralNode::LiteralNode(double _double){
	d_literal.d_double = _double;

	base_type = t_double;
	derived_type = t_none;

	code = to_string(_double);
#ifdef DEBUG
	std::cout << base_type << " " << code << std::endl;
#endif
}

LiteralNode::LiteralNode(string *_string){
	d_literal.d_string = _string;

	base_type = t_string;
	derived_type = t_none;

	code = *_string;
#ifdef DEBUG
	std::cout << base_type << " " << code << std::endl;
#endif
}

}
}