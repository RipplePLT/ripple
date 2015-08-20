#ifndef INCLUDED_LITERAL_NODE
#define INCLUDED_LITERAL_NODE

#ifndef INCLUDED_AST_NODE
#include "ast_node.h"
#endif

namespace Ripple {
namespace AST {

namespace {
	union value {
		bool d_bool;
		int d_int;
		double d_double;
		string *d_string;
	};
}

class LiteralNode : public ASTNode {
private:
	value d_value;

public:
	LiteralNode(bool _bool);
	LiteralNode(int _int);
	LiteralNode(double _double);
	LiteralNode(string *_string);
};

}
}

#endif