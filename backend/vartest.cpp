#include <iostream>
#include "linked_var.hpp"
#include "variable_tree.hpp"

int main()
{
    int x, y;
	struct link_val temp_link_val;

	// @TODO everything on the heap

	// link (x <- 5)
	LiteralNode l (5);
	ValueNode v (&l);
	UnaryExpressionNode u (&v);
	BinaryExpressionNode b_x (&u);
	ExpressionNode e_x (&b_x);
    Linked_Var var_x (&x, e_x);

    /* link (y <- x + 2) */
	VariableNode l1 (&x);
	ValueNode v1 (&l1);
	LiteralNode l2 (2);
    ValueNode v2 (&l2);
    UnaryExpressionNode u1 (&v1);
    UnaryExpressionNode u2 (&v2);
    BinaryExpressionNode b1 (&u1);
    BinaryExpressionNode b2 (&u2);
    BinaryExpressionNode b_y (&b1, "+", &b2);
    ExpressionNode e_y (&b_y);
	Linked_Var var_y (&y, e_y);

	// @TODO dynamically detect & assign refs
	vector<Linked_Var*> x_refs;
	x_refs.push_back(&var_y);
	Linked_Var::references[&x] = x_refs;

	cout << "x == " << var_x.get_value().value.intval << endl;
	cout << "y == " << var_y.get_value().value.intval << endl;
	
	x = 6;
	// problem -- x is linked to 5. evaluating x sets x back to 5.
	// var_x.update();
	var_y.update();

	cout << "x == " << var_x.get_value().value.intval << endl;
	cout << "y == " << var_y.get_value().value.intval << endl;

    return 0;
}
