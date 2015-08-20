#ifndef INCLUDED_LITERAL_NODE
#include "literal_node.h"
#endif

namespace Ripple {
namespace AST {

LiteralNode::LiteralNode(bool _bool){
	d_value.d_bool = _bool;

	base_type = t_bool;
	derived_type = t_none;

	code = to_string(_bool);
}

LiteralNode::LiteralNode(int _int){
	d_value.d_int = _int;

	base_type = t_bool;
	derived_type = t_none;

	code = to_string(_int);
}

LiteralNode::LiteralNode(double _double){
	d_value.d_double = _double;

	base_type = t_bool;
	derived_type = t_none;

	code = to_string(_double);
}

LiteralNode::LiteralNode(string *_string){
	d_value.d_string = _string;

	base_type = t_bool;
	derived_type = t_none;

	code = *_string;
}

}
}