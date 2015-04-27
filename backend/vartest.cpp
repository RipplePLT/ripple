#include <iostream>
#include "linked_var.hpp"
#include "expression_tree.hpp"

/*
 * This test is an example of the intermediate code that link
 * statements will compile to.
 */
int main()
{
    int x, y;
	int root;

	/*
     * @TODO Everything must be allocated on the heap, since both
	 * threads need access to it.
	 */

	// Assignment to a Ripple or C++ int is the same.
	cout << "root = 5;" << endl;
	root = 5;

	/* === Link Statement ===
     * 		link (x <- root);
	 */
	cout << "link (x <- root);" << endl;
	VariableNode l (&root);
    ValueNode v (&l);
    UnaryExpressionNode u (&v);
    BinaryExpressionNode b_x (&u);
    ExpressionNode e_x (&b_x);
    linked_var var_x (&x, e_x);
	/* === End of code for link (x <- root) === */

    /* === Link Statement ===
	 * 		link (y <- x + 2)
	 */
	cout << "link (y <- x + 2);" << endl;
    VariableNode l1 (&x);
    ValueNode v1 (&l1);
    LiteralNode l2 (2);
    ValueNode v2 (&l2);
    UnaryExpressionNode u1 (&v1);
    UnaryExpressionNode u2 (&v2);
    BinaryExpressionNode b1 (&u1);
    BinaryExpressionNode b2 (&u2);
    // BinaryExpressionNode b_y (&b1, "+", &b2);
    BinaryExpressionNode b_y (&b1, "*", &b2);
    ExpressionNode e_y (&b_y);
    linked_var var_y (&y, e_y);

	// Assign references
	// @TODO these must be detected and assigned dynamically
    vector<linked_var *> x_refs;
    x_refs.push_back(&var_y);
    linked_var::references[&x] = x_refs;
	/* === End of code for "link (y <- x + 2)" === */

    cout << "x == " << *(int *)var_x.get_value().value.ptr << endl;
    cout << "y == " << var_y.get_value().value.intval << endl;

	/*
	 * === Assignment ===
	 * 		root = 6;
	 */
	cout << "root = 6;" << endl;
    root = 6;
    var_x.update();
	/* === End of code for "root = 6" === */

    cout << "x == " << *(int *)var_x.get_value().value.ptr << endl;
    cout << "y == " << var_y.get_value().value.intval << endl;

    return 0;
}
