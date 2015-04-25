#include <stdio.h>
#include "linked_var.hpp"
#include "../frontend/symbol_table/hashmap.h"
#include "../frontend/ast.h"

int line_no = 0;

int main()
{
    // int x, y;

	/**********************************/
	/***** YACC DOES THIS *************/
	/**********************************/

	// Build RHS ExpressionNode for x = 5
	LiteralNode l (5);
	ValueNode v (&l);
	UnaryExpressionNode u (&v);
	BinaryExpressionNode b_x (&u);
	ExpressionNode e_x (&b_x);

    // Build RHS ExpressionNode for y = x + 2
	Entry x_entry ("x", tNONE, 0);
	IDNode i (&x_entry);
    ValueNode v1 (&i);
	LiteralNode l2 (2);
    ValueNode v2 (&l2);
    UnaryExpressionNode u1 (&v1);
    UnaryExpressionNode u2 (&v2);
    BinaryExpressionNode b1 (&u1);
    BinaryExpressionNode b2 (&u2);
    BinaryExpressionNode b_y (&b1, "+", &b2);
    ExpressionNode e_y (&b_y);

/*
    Linked_Var var_x (&x, e_x);
	Linked_Var var_y (&y, e_y);

	var_x.add_reference(&var_y);

	fprintf(stderr, "x = %d\n", var_x.get_value());
	fprintf(stderr, "y = %d\n", var_y.get_value());
*/

    return 0;
}
