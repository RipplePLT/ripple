#include <iostream>
#include "linked_var.hpp"
#include "expression_tree.hpp"
#include "sync_queue.hpp"

/*
 * This test is an example of the intermediate code that link
 * statements will compile to.
 */
int main()
{
    int x, y;
	int root;

	/*
     * Everything is allocated on the heap, since all threads need
	 * access to this data.
	 */

	// Assignment to a Ripple or C++ int is the same.
	cout << "root = 5;" << endl;
	root = 5;

	/* === Link Statement ===
     * 		link (x <- root);
	 */
	cout << "link (x <- root);" << endl;
	VariableNode *l = new VariableNode (&root);
	linked_var::references[&root] = new vector<linked_var*>();
    ValueNode *v = new ValueNode (l);
    UnaryExpressionNode *u = new UnaryExpressionNode (v);
    BinaryExpressionNode *b_x = new BinaryExpressionNode (u);
    ExpressionNode *e_x = new ExpressionNode (b_x);
    linked_var *var_x = new linked_var (&x, e_x);
	/* === End of code for link (x <- root) === */

    /* === Link Statement ===
	 * 		link (y <- x + 2)
	 */
	cout << "link (y <- x + 2);" << endl;
    VariableNode *l1 = new VariableNode (&x);
	linked_var::references[&x] = new vector<linked_var*>();
    ValueNode *v1 = new ValueNode (l1);
    LiteralNode *l2 = new LiteralNode (2);
    ValueNode *v2 = new ValueNode (l2);
    UnaryExpressionNode *u1 = new UnaryExpressionNode (v1);
    UnaryExpressionNode *u2 = new UnaryExpressionNode (v2);
    BinaryExpressionNode *b1 = new BinaryExpressionNode (u1);
    BinaryExpressionNode *b2 = new BinaryExpressionNode (u2);
    BinaryExpressionNode *b_y = new BinaryExpressionNode (b1, "+", b2);
    ExpressionNode *e_y = new ExpressionNode (b_y);
    linked_var *var_y = new linked_var (&y, e_y);
	/* === End of code for "link (y <- x + 2)" === */

    cout << "\tx == " << *(int *)var_x->get_value().value.ptr << endl;
    cout << "\ty == " << var_y->get_value().value.intval << endl;

	/*
	 * === Assignment ===
	 * 		root = 6;
	 */
	cout << "root = 6;" << endl;
    root = 6;
	// @TODO use the sync_queue for updates
    var_x->update();
	/* === End of code for "root = 6" === */

    cout << "\tx == " << *(int *)var_x->get_value().value.ptr << endl;
    cout << "\ty == " << var_y->get_value().value.intval << endl;

    return 0;
}
