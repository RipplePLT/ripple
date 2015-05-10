#include <iostream>
#include <cmath>
#include <assert.h>
#include "../expression_tree.h"
#include "../link_val.h"
#include "../linked_var.h"
#include "../streamreader/keyboard_stream_reader.h"

/* Spaghetti */

class TreeTest {
public:
	static VariableNode *create_var_node(int *i);
	static VariableNode *create_var_node(double *d);
	static LiteralNode *create_literal_node(int i);
	static LiteralNode *create_literal_node(double d);
	static linked_var *link_int_var(int *i);
	static linked_var *link_double_var(double *d);
	static linked_var *link_bool_lit_op_bool_var
		(void *linked, bool b, bool *d, const char *op);
	static linked_var *link_int_lit_op_double_var
		(void *linked, int i, double *d, const char *op);
	static void test_unary_ops();
	static void test_nested_expressions();
	static void test_string_concatenation();
	static void test_string_int_concatenation();
	static void test_aux_fn_expressions();
	static void test_streamreader_int_expressions();
	static void test_streamreader_string_expressions();
	static void run_all_unit_tests();
	static void run_all_integration_tests();
};

void test_aux_fn (int n) {
	cerr << "[AUX_FN] " << n << endl;
}

void test_aux_str_fn (string n) {
	cerr << "[AUX_FN] " << n << endl;
}

int rpl_str_to_int (string msg) {
	return atoi(msg.c_str());
}

string default_rpl_str_str (string msg) {
	return msg;
}

void TreeTest::test_streamreader_int_expressions() {
	cerr << "y <- x + 2" << endl;
	cerr << "Enter x." << endl;

	int y, x = 2;
	linked_var::register_cpp_var(&x);
	linked_var::register_cpp_var(&y);

	// link (y <- x + 2)
	//     text_aux_fn(y);
	linked_var *y_var = new linked_var(&y, new ExpressionNode (
		new BinaryExpressionNode(
			new BinaryExpressionNode(
				new UnaryExpressionNode(
				new ValueNode(
				new VariableNode(&x)))), "+",
			new BinaryExpressionNode(
				new UnaryExpressionNode(
				new ValueNode(
				new LiteralNode(2)))))));
	y_var->assign_aux_fn((void *)&test_aux_fn);

	// link (x <- str_to_int <- KSR());
	int stream;
	FuncPtr<int>::f_ptr f = &rpl_str_to_int; 
	KeyboardStreamReader<int> *sr = new KeyboardStreamReader<int>(&stream, f);
	linked_var::register_cpp_var(&stream);
	linked_var *sr_var = new linked_var(&x, new ExpressionNode (
		new BinaryExpressionNode(
		new UnaryExpressionNode(
		new ValueNode(
		new VariableNode(&stream))))));


	sr->start_thread();
	while (1) {}
}

void TreeTest::test_streamreader_string_expressions() {
	string *prefix = new string("Ripple is ");
	string *suffix = new string();
	string *sentence = new string();

	linked_var::register_cpp_var(prefix);
	linked_var::register_cpp_var(suffix);
	linked_var::register_cpp_var(sentence);

	// link (sentence <- prefix + suffix)
	//		test_aux_str_fn(sentence);
	linked_var *sentence_var = new linked_var(sentence, new ExpressionNode(
		new BinaryExpressionNode(
			new BinaryExpressionNode(
				new UnaryExpressionNode(
				new ValueNode(
				new VariableNode((string **)prefix)))), "+",
			new BinaryExpressionNode(
				new UnaryExpressionNode(
				new ValueNode(
				new VariableNode((string **)suffix)))))));
	sentence_var->assign_aux_fn((void *)&test_aux_str_fn);

	// link (suffix <- str_to_str <- KSR());
	string *stream = new string();
	linked_var::register_cpp_var(stream);
	FuncPtr<string>::f_ptr f = &default_rpl_str_str;  // @TODO !!! default
	KeyboardStreamReader<string> *sr = new KeyboardStreamReader<string>(suffix, f);
	linked_var *suffix_var = new linked_var(suffix, new ExpressionNode (
		new BinaryExpressionNode(
		new UnaryExpressionNode(
		new ValueNode(
		new VariableNode((string **)stream))))));

	sr->start_thread();
	while (1) {}
}

void TreeTest::test_aux_fn_expressions() {
	int y, x = 2;
	linked_var::register_cpp_var(&x);
	linked_var::register_cpp_var(&y);

	// link (y <- x + 2)
	//     text_aux_fn(y);
	linked_var *y_var = new linked_var(&y, new ExpressionNode (
		new BinaryExpressionNode(
			new BinaryExpressionNode(
				new UnaryExpressionNode(
				new ValueNode(
				new VariableNode(&x)))), "+",
			new BinaryExpressionNode(
				new UnaryExpressionNode(
				new ValueNode(
				new LiteralNode(2)))))));
	y_var->assign_aux_fn((void *)&test_aux_fn);

	// x = 100;
	x = 100;
	linked_var::update_nonlinked_var(&x);

	assert(y == 102);
}

void TreeTest::test_nested_expressions() {
	int z, x = 1;
	linked_var::register_cpp_var(&x);
	linked_var::register_cpp_var(&z);

	// link (z <- (2 + x) + 2)
	linked_var *z_var = new linked_var(&z, new ExpressionNode (
		new BinaryExpressionNode(
			new BinaryExpressionNode(
			new UnaryExpressionNode(
			new ValueNode(
			new ExpressionNode(
				new BinaryExpressionNode(
					new BinaryExpressionNode(
						new UnaryExpressionNode(
						new ValueNode(
						new LiteralNode(2)))), "+",
					new BinaryExpressionNode(
						new UnaryExpressionNode(
						new ValueNode(
						new VariableNode(&x))))))))), "+",
			new BinaryExpressionNode(
			new UnaryExpressionNode(
			new ValueNode(
			new LiteralNode(2)))))));

	assert(z == 5);

	x = 100;
	linked_var::update_nonlinked_var(&x);

	assert(z == 104);
	linked_var::reset_refs();
}

void TreeTest::test_string_int_concatenation() {
	LiteralNode *prefix_litnode = new LiteralNode("We have ");
	LiteralNode *suffix_litnode =
		new LiteralNode(" days left to satisfy Aho.");
	
	int num = 4;
	linked_var::register_cpp_var(&num);
	VariableNode *num_varnode = new VariableNode(&num);

	ValueNode *prefix_valnode = new ValueNode(prefix_litnode);
	ValueNode *suffix_valnode = new ValueNode(suffix_litnode);
	ValueNode *num_valnode = new ValueNode(num_varnode);

	UnaryExpressionNode *prefix_unode =
		new UnaryExpressionNode(prefix_valnode);
	UnaryExpressionNode *suffix_unode =
		new UnaryExpressionNode(suffix_valnode);
	UnaryExpressionNode *num_unode =
		new UnaryExpressionNode(num_valnode);

	BinaryExpressionNode *prefix_bnode =
		new BinaryExpressionNode(prefix_unode);
	BinaryExpressionNode *suffix_bnode =
		new BinaryExpressionNode(suffix_unode);
	BinaryExpressionNode *num_bnode = 
		new BinaryExpressionNode(num_unode);

	ExpressionNode *num_enode =
		new ExpressionNode(num_bnode);
	linked_var *num_var = new linked_var (&num, num_enode);

	BinaryExpressionNode *low_link =
		new BinaryExpressionNode(prefix_bnode, "+", num_bnode);
	BinaryExpressionNode *high_link =
		new BinaryExpressionNode(low_link, "+", suffix_bnode);
	
	string *despair = new string();
	linked_var::register_cpp_var(&despair);
	ExpressionNode *despair_enode =
		new ExpressionNode(high_link);
	linked_var *despair_var =
		new linked_var (despair, despair_enode);

	for (num = 4; num >= 0; num--) {
		linked_var::update_nonlinked_var(&num);
		cerr << despair_var->get_value().value.strval->c_str() << endl;
		assert (!strcmp(despair_var->get_value().value.strval->c_str(),
			despair->c_str()));
	}

	cerr << "[TREE_TEST] String-int concatenation passed, but satisfying Aho failed." << endl;
}

void TreeTest::test_string_concatenation() {
	// Make variable node
	// [rpl] string predicate = "a problem.";
	string *predicate = new string ("a problem.");
	linked_var::register_cpp_var(predicate);
	VariableNode *predicate_varnode = new VariableNode((string **)predicate);
	ValueNode *predicate_valnode = new ValueNode (predicate_varnode);
	UnaryExpressionNode *predicate_unode =
		new UnaryExpressionNode (predicate_valnode);
	BinaryExpressionNode *predicate_bnode =
		new BinaryExpressionNode (predicate_unode);
	ExpressionNode *predicate_enode =
		new ExpressionNode (predicate_bnode);
	linked_var *predicate_var =
		new linked_var (predicate, predicate_enode);

	assert(predicate_var->get_value().type == ltSTR_PTR);
	assert(!strcmp((*(string *)predicate_var->get_value().value.ptr).c_str(), "a problem."));

	// [rpl] link (string sentence <- "Amar says: we have " + predicate);
	string *sentence = new string();
	linked_var::register_cpp_var(sentence);

	LiteralNode *prefix_litnode = new LiteralNode("Amar says: we have ");
	ValueNode *prefix_valnode = new ValueNode(prefix_litnode);
	UnaryExpressionNode *prefix_unode =
		new UnaryExpressionNode (prefix_valnode);
	BinaryExpressionNode *prefix_bnode =
		new BinaryExpressionNode (prefix_unode);

	BinaryExpressionNode *sentence_bnode =
		new BinaryExpressionNode (prefix_bnode, "+", predicate_bnode);
	ExpressionNode *sentence_enode =
		new ExpressionNode (sentence_bnode);
	linked_var *sentence_var =
		new linked_var (sentence, sentence_enode);

	assert(sentence_var->get_value().type == ltSTR);
	assert(!strcmp((*(string *)(sentence_var->get_value().value.ptr)).c_str(), "Amar says: we have a problem."));

	// Change suffix
	// [rpl] predicate = "no problem.";
	predicate = new string ("no problem.");
	linked_var::update_nonlinked_var(predicate);

	assert(!strcmp((*(string *)(sentence_var->get_value().value.ptr)).c_str(), "Amar says: we have a problem."));
	assert(strcmp((*(string *)(sentence_var->get_value().value.ptr)).c_str(), "Amar says: we have no problem."));

	linked_var::reset_refs();
}

void TreeTest::test_unary_ops() {
	bool root;
	LiteralNode *bLit = new LiteralNode(true);

	assert(bLit->evaluate().size_node().value.intval == sizeof(bool));

	ValueNode *v = new ValueNode(bLit);
	UnaryExpressionNode *u = new UnaryExpressionNode(v);
	UnaryExpressionNode *u2 = new UnaryExpressionNode(u, "not");
	BinaryExpressionNode *b = new BinaryExpressionNode(u2);
	ExpressionNode *e = new ExpressionNode(b);
	linked_var *root_var = new linked_var(&root, e);

	bool root2 = false;
	VariableNode *bVar = new VariableNode(&root2);
	linked_var::references[&root2] = new vector<linked_var*>();

	assert(bVar->evaluate().size_node().value.intval == sizeof(bool *));
	
	ValueNode *v2 = new ValueNode(bVar);
	UnaryExpressionNode *u3 = new UnaryExpressionNode(v2);
	UnaryExpressionNode *u4 = new UnaryExpressionNode(u3, "not");
	BinaryExpressionNode *b2 = new BinaryExpressionNode(u4);
	ExpressionNode *e2 = new ExpressionNode(b2);
	linked_var *root2_var = new linked_var(&root2, e2);

	assert(root_var->get_value().type == ltBOOL);
	assert(root_var->get_value().value.boolval == false);
	assert(root2_var->get_value().type == ltBOOL);
	assert(root2_var->get_value().value.boolval == true);

	linked_var::reset_refs();
}

VariableNode *TreeTest::create_var_node(int *i) {
    // Code
    VariableNode *v = new VariableNode (i);

    // Test
    assert(v->val.type == ltINT_PTR);
    assert(v->val.value.ptr == (void *)i);
    assert(v->var == i);
    assert(v->dependencies->size() == 1);
    assert((*v->dependencies)[0] == i);

    return v;
}

VariableNode *TreeTest::create_var_node(double *d) {
    // Code
    VariableNode *v = new VariableNode (d);

    // Test
    assert(v->val.type == ltDOUBLE_PTR);
    assert(v->val.value.ptr == (void *)d);
    assert(v->var == d);
    assert(v->dependencies->size() == 1);
    assert((*v->dependencies)[0] == d);

    return v;
}

LiteralNode *TreeTest::create_literal_node(int i) {
    LiteralNode *l = new LiteralNode(i);

    assert(l->val.type == ltINT);
    assert(l->val.value.intval == i);

    return l;
}

LiteralNode *TreeTest::create_literal_node(double d) {
    LiteralNode *l = new LiteralNode(d);

    assert(l->val.type == ltDOUBLE);
    assert(l->val.value.doubleval == d);

    return l;
}

void TreeTest::run_all_unit_tests() {
    int a = 5;
    int b = 0;
    double c = 5.5;
    double d = 5;
    double e = 0;

    /* VariableNode */
    create_var_node(&a);
    create_var_node(&b);
    create_var_node(&c);
    create_var_node(&d);
    create_var_node(&e);

    /* LiteralNode */
    create_literal_node(a);
    create_literal_node(b);
    create_literal_node(c);
    create_literal_node(d);
    create_literal_node(e);

	linked_var::reset_refs();
}

/* Link to one integer variable */
linked_var *TreeTest::link_int_var(int *i) {
    // Code
    VariableNode *v = new VariableNode (i);

    // Test
    assert(v->val.type == ltINT_PTR);
    assert(v->val.value.ptr == (void *)i);
    assert(v->var == i);
    assert(v->dependencies->size() == 1);
    assert((*v->dependencies)[0] == i);

    // Code
    linked_var::references[i] = new vector<linked_var*>();
    ValueNode *valNode = new ValueNode (v);

    // Test
    assert(valNode->is_literal == false);
    assert(valNode->var_node == v);
    assert(valNode->dependencies->size() == 1);
    assert((*valNode->dependencies)[0] == i);
    assert(v->evaluate().value.ptr == i);
    assert(v->evaluate().type == ltINT_PTR);

    // Code
    UnaryExpressionNode *u = new UnaryExpressionNode (valNode);

    // Test
    assert(u->op == NONE);
    assert(u->right_operand.v_node == valNode);
    assert(u->dependencies == valNode->dependencies);
    assert(u->evaluate().value.ptr == i);
    assert(u->evaluate().type == ltINT_PTR);

    // Code
    BinaryExpressionNode *b_x = new BinaryExpressionNode (u);
    assert(b_x->left_operand.u_exp == u);
    assert(b_x->op == NONE);
    assert(b_x->dependencies == u->dependencies);
    assert(b_x->evaluate().value.ptr == i);
    assert(b_x->evaluate().type == ltINT_PTR);

    // Code
    ExpressionNode *e_x = new ExpressionNode (b_x);

    // Test
    assert(e_x->bin_exp == b_x);
    assert(e_x->value == NULL);
    assert(e_x->dependencies == b_x->dependencies);
    assert(e_x->evaluate().value.ptr == i);
    assert(e_x->evaluate().type == ltINT_PTR);

    // Code
    linked_var *var_x = new linked_var (i, e_x);
    assert(var_x->get_value().value.ptr == i);
    assert(var_x->get_value().type == ltINT_PTR);

    return var_x;
}

/* Link to one double variable */
linked_var *TreeTest::link_double_var(double *d) {
    // Code
    VariableNode *v = new VariableNode (d);

    // Test
    assert(v->val.type == ltDOUBLE_PTR);
    assert(v->val.value.ptr == (void *)d);
    assert(v->var == d);
    assert(v->dependencies->size() == 1);
    assert((*v->dependencies)[0] == d);

    // Code
    linked_var::references[d] = new vector<linked_var*>();
    ValueNode *valNode = new ValueNode (v);

    // Test
    assert(valNode->is_literal == false);
    assert(valNode->var_node == v);
    assert(valNode->dependencies->size() == 1);
    assert((*valNode->dependencies)[0] == d);
    assert(v->evaluate().value.ptr == d);
    assert(v->evaluate().type == ltDOUBLE_PTR);

    // Code
    UnaryExpressionNode *u = new UnaryExpressionNode (valNode);

    // Test
    assert(u->op == NONE);
    assert(u->right_operand.v_node == valNode);
    assert(u->dependencies == valNode->dependencies);
    assert(u->evaluate().value.ptr == d);
    assert(u->evaluate().type == ltDOUBLE_PTR);

    // Code
    BinaryExpressionNode *b_x = new BinaryExpressionNode (u);
    assert(b_x->left_operand.u_exp == u);
    assert(b_x->op == NONE);
    assert(b_x->dependencies == u->dependencies);
    assert(b_x->evaluate().value.ptr == d);
    assert(b_x->evaluate().type == ltDOUBLE_PTR);

    // Code
    ExpressionNode *e_x = new ExpressionNode (b_x);

    // Test
    assert(e_x->bin_exp == b_x);
    assert(e_x->value == NULL);
    assert(e_x->dependencies == b_x->dependencies);
    assert(e_x->evaluate().value.ptr == d);
    assert(e_x->evaluate().type == ltDOUBLE_PTR);

    // Code
    linked_var *var_x = new linked_var (d, e_x);
    assert(var_x->get_value().value.ptr == d);
    assert(var_x->get_value().type == ltDOUBLE_PTR);

    return var_x;
}

/* Link to int literal (op) double var */
linked_var *TreeTest::link_int_lit_op_double_var(void *linked, int i,
        double *d, const char *op) {
    // Determine target value
    double target;
    if (!strcmp(op, "+"))
        target = i + *d;
    else if (!strcmp(op, "-"))
        target = i - *d;
    else if (!strcmp(op, "*"))
        target = i * *d;
    else if (!strcmp(op, "/"))
        target = i / *d;
    else if (!strcmp(op, "^"))
        target = pow(i, *d);
    else
        target = 0;

    // Left operand
    LiteralNode *l1 = new LiteralNode(i);
    ValueNode *v1 = new ValueNode(l1);
    UnaryExpressionNode *u1 = new UnaryExpressionNode(v1);
    BinaryExpressionNode *b1 = new BinaryExpressionNode(u1);
    assert(b1->evaluate().value.intval == i);
    assert(b1->evaluate().type == ltINT);

    // Right operand
    VariableNode *l2 = new VariableNode(d);
    ValueNode *v2 = new ValueNode (l2);
    UnaryExpressionNode *u2 = new UnaryExpressionNode(v2);
    BinaryExpressionNode *b2 = new BinaryExpressionNode(u2);
    assert(b2->evaluate().value.ptr == d);
    assert(b2->evaluate().type == ltDOUBLE_PTR);

    // Operation
    BinaryExpressionNode *bin = new BinaryExpressionNode (b1, op, b2);
    if (link_val::is_bool_op(op)) {
        assert(bin->evaluate().type == ltBOOL);
    } else {
        assert(bin->evaluate().type == ltDOUBLE);
        assert(bin->evaluate().value.doubleval == target);
    }

    ExpressionNode *exp = new ExpressionNode(bin);
    linked_var *var = new linked_var(linked, exp);

    return var;
}

/* Link to bool literal (op) bool var */
linked_var *TreeTest::link_bool_lit_op_bool_var(void *linked, bool i,
        bool *d, const char *op) {
    // Determine target value
    bool target;
    if (!strcmp(op, "and"))
        target = i && *d;
    else if (!strcmp(op, "or"))
        target = i || *d;
    else
        target = false;

    // Left operand
    LiteralNode *l1 = new LiteralNode(i);
    ValueNode *v1 = new ValueNode(l1);
    UnaryExpressionNode *u1 = new UnaryExpressionNode(v1);
    BinaryExpressionNode *b1 = new BinaryExpressionNode(u1);
    assert(b1->evaluate().value.boolval == i);
    assert(b1->evaluate().type == ltBOOL);

    // Right operand
    VariableNode *l2 = new VariableNode(d);
    ValueNode *v2 = new ValueNode (l2);
    UnaryExpressionNode *u2 = new UnaryExpressionNode(v2);
    BinaryExpressionNode *b2 = new BinaryExpressionNode(u2);
    assert(b2->evaluate().value.ptr == d);
    assert(b2->evaluate().type == ltBOOL_PTR);

    // Operation
    BinaryExpressionNode *bin = new BinaryExpressionNode (b1, op, b2);
    assert(bin->evaluate().type == ltBOOL);
    assert(bin->evaluate().value.boolval == target);

    ExpressionNode *exp = new ExpressionNode(bin);
    linked_var *var = new linked_var(linked, exp);

    return var;
}

void TreeTest::run_all_integration_tests() {
	assert(linked_var::references.size() == 0);

	int a = 5;
	link_int_var(&a);

	double b = 2.5;
	link_double_var(&b);

	double z;
	linked_var *z_link;
	z_link = link_int_lit_op_double_var(&z, a, &b, "+");
	assert(z_link->get_value().type == ltDOUBLE);
	assert(z_link->get_value().value.doubleval == 7.5);

	z_link = link_int_lit_op_double_var(&z, a, &b, "-");
	assert(z_link->get_value().value.doubleval == 2.5);

	z_link = link_int_lit_op_double_var(&z, a, &b, "*");
	assert(z_link->get_value().value.doubleval == 12.5);

	z_link = link_int_lit_op_double_var(&z, a, &b, "/");
	assert(z_link->get_value().value.doubleval == 2);

	bool q;
	z_link = link_int_lit_op_double_var(&q, a, &b, ">");
	assert(z_link->get_value().value.boolval == true);
	z_link = link_int_lit_op_double_var(&q, a, &b, ">=");
	assert(z_link->get_value().value.boolval == true);

	z_link = link_int_lit_op_double_var(&q, a, &b, "<");
	assert(z_link->get_value().value.boolval == false);
	z_link = link_int_lit_op_double_var(&q, a, &b, "<=");
	assert(z_link->get_value().value.boolval == false);

	b = 5;
	z_link = link_int_lit_op_double_var(&q, a, &b, ">=");
	assert(z_link->get_value().value.boolval == true);
	z_link = link_int_lit_op_double_var(&q, a, &b, "<=");
	assert(z_link->get_value().value.boolval == true);
	z_link = link_int_lit_op_double_var(&q, a, &b, "==");
	assert(z_link->get_value().value.boolval == true);
	z_link = link_int_lit_op_double_var(&q, a, &b, "!=");
	assert(z_link->get_value().value.boolval == false);

	a = 5, b = 2;
	z_link = link_int_lit_op_double_var(&z, a, &b, "^");
	assert(z_link->get_value().value.doubleval == 25);

	bool r = true;
	linked_var *r_link;
	linked_var::references[&r] = new vector<linked_var*>();
	r_link = link_bool_lit_op_bool_var(&r, (3 > 2), &r, "and");
	assert(r_link->get_value().value.boolval == true);
	r_link = link_bool_lit_op_bool_var(&r, (2 > 2), &r, "and");
	assert(r_link->get_value().value.boolval == false);
	r = false;
	r_link = link_bool_lit_op_bool_var(&r, (3 > 2), &r, "or");
	assert(r_link->get_value().value.boolval == true);
	r_link = link_bool_lit_op_bool_var(&r, (2 > 2), &r, "or");
	assert(r_link->get_value().value.boolval == false);

	test_unary_ops();
	cerr << "[TREE_TEST] All unary operation tests passed." << endl;
	linked_var::reset_refs();

	test_string_concatenation();
	cerr << "[TREE_TEST] String-string concatenation test passed." << endl;
	linked_var::reset_refs();
	test_string_int_concatenation();
	cerr << "[TREE_TEST] All string operation tests passed." << endl;
	linked_var::reset_refs();
	test_nested_expressions();
	cerr << "[TREE_TEST] Nested expression tests passed." << endl;
	linked_var::reset_refs();
	test_aux_fn_expressions();
	cerr << "[TREE_TEST] Auxiliary link function tests passed." << endl;
	linked_var::reset_refs();
	//test_streamreader_int_expressions();
	test_streamreader_string_expressions();
	linked_var::reset_refs();
}

int main() {
    TreeTest::run_all_unit_tests();
	cerr << "[TREE_TEST] All unit tests passed." << endl;
    TreeTest::run_all_integration_tests();

    cerr << "[TREE_TEST] All tests passed." << endl;
}
