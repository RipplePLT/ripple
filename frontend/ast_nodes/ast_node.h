#ifndef INCLUDED_AST_NODE
#define INCLUDED_AST_NODE

#include <string>
#include <string.h>

namespace Ripple {
namespace AST {

using namespace std;

enum d_base_type {
	t_bool = 0,
	t_int = 1,
	t_double = 2,
	t_string = 3
};

enum d_derived_type {
	t_none = 0,
	t_array = 1,
	t_dataset = 2
};

class ASTNode {
public:
	string code;
	d_base_type base_type;
	d_derived_type derived_type;
};

}
}

#endif