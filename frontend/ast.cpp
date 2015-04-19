#include "ast.h"
#include <string>

enum e_op str_to_op(const std::string op_string) {
    if(op_string.compare("+") == 0)
        return PLUS;
    else if (op_string.compare("-") == 0)
        return MINUS;
    else if (op_string.compare("*") == 0)
        return TIMES;
    else if (op_string.compare("/") == 0)
        return DIV;
    else if (op_string.compare("//") == 0)
        return FLDIV;
    else if (op_string.compare("^") == 0)
        return EXP;
    else if (op_string.compare("and") == 0)
        return bAND;
    else if (op_string.compare("or") == 0)
        return bOR;
    else if (op_string.compare("not") == 0)
        return bNOT;
    else if (op_string.compare("==") == 0)
        return EQ;
    else if (op_string.compare("!=") == 0)
        return NE;
    else if (op_string.compare(">") == 0)
        return GT;
    else if (op_string.compare("<") == 0)
        return LT;
    else if (op_string.compare(">=") == 0)
        return GE;
    else if (op_string.compare("<=") == 0)
        return LE;
    else if (op_string.compare("@") == 0)
        return SIZE;
};

enum e_type str_to_type(const std::string type){
    if (type.compare("INT") == 0)
        return tINT;
    else if (type.compare("FLOAT") == 0)
        return tFLOAT;
    else if (type.compare("VOID") == 0)
        return tVOID;
    else if (type.compare("BOOL") == 0)
        return tBOOL;
    else if (type.compare("STRING") == 0)
        return tSTRING;
    else if (type.compare("BYTE") == 0)
        return tBYTE;
}

enum e_jump str_to_jump(const std::string type){
    if (type.compare("RETURN") == 0)
        return tRETURN;
    else if (type.compare("BREAK") == 0)
        return tBREAK;
    else if (type.compare("CONTINUE") == 0)
        return tCONTINUE;
}

string gen_binary_code(string l_code, enum e_op op, string r_code){
    string code;
    switch(op) {
        case PLUS:
            code = l_code + " + " + r_code;
            break;
        case MINUS:
            code = l_code + " - " + r_code;
            break;
        case TIMES:
            code = l_code + " * " + r_code;
            break;
        case DIV:
            code = l_code + " / " + r_code;
            break;
        case FLDIV:
            code = "(double)" + l_code + "/ (double)" + r_code;
            break;
        case EXP:
            code = "Math.pow(" + l_code + ", " + r_code + ")";
            break;
        case bAND:
            code = l_code + " && " + r_code;
            break;
        case bOR:
            code = l_code + " || " + r_code;
            break;
        case EQ:
            code = l_code + " == " + r_code;
            break;
        case NE:
            code = l_code + " != " + r_code;
            break;
        case GT:
            code = l_code + " > " + r_code;
            break;
        case LT:
            code = l_code + " < " + r_code;
            break;
        case GE:
            code = l_code + " >= " + r_code;
            break;
        case LE:
            code = l_code + " <= " + r_code;
            break;
        default:
            code = "";
            break;
    }
    return code;
}

/* Node */
e_type Node::get_type() {
    return type;
}

/* ValueNode */
ValueNode::ValueNode(IDNode *i) {
    val.id_val = i;
    type = i->type;
    code = i->code;
}
ValueNode::ValueNode(LiteralNode *l) {
    val.lit_val = l;
    type = l->type;
    code = l->code;
}
ValueNode::ValueNode(FunctionCallNode *f) {
    val.function_call_val = f;
    type = f->type;
    code = f->code;
} 
ValueNode::ValueNode(ArrayAccessNode *a) {
    val.array_access_val = a;
    type = a->type;
    code = a->code;
}
ValueNode::ValueNode(DatasetAccessNode *d) {
    val.dataset_access_val = d;
    type = d->type;
    code = d->code;
}
ValueNode::ValueNode(ExpressionNode *e) {
    val.expression_val = e;
    type = e->type;
    code = "( " + e->code + " )";
}

/* IDNode */
IDNode::IDNode(Entry *ent) {
    entry = ent;
    type = ent->type;
    code = ent->name;
}
IDNode::~IDNode() { }

/* FunctionCallNode */
FunctionCallNode::FunctionCallNode(IDNode *f, ArgsNode *a) {
    func_name = f;
    args_list = a;
    type = f->type;
    code = f->code + "( " + a->code + " )";
}
FunctionCallNode::FunctionCallNode(IDNode *f) {
    func_name = f;
    type = f-> type;
    code = f->code + "()";
}

/* ArgsNode */
ArgsNode::ArgsNode() {
    code = "";
}
ArgsNode::ArgsNode(ExpressionNode *arg) {
    args_list.push_back(arg);
    code = arg->code;
}
void ArgsNode::add_arg(ExpressionNode *arg) {
    args_list.push_back(arg);

    if(code.compare("") == 0)
        code += arg->code;
    else
        code += ", " + arg->code;
}

/* DeclArgsNode */
DeclArgsNode::DeclArgsNode() {
    code = "";
}
DeclArgsNode::DeclArgsNode(IDNode* arg) {
    decl_args_list.push_back(arg); code = arg->code;
}
void DeclArgsNode::add_arg(IDNode* arg) {
    decl_args_list.push_back(arg);
    code += arg->code;
}

/* LiteralNode */
LiteralNode::LiteralNode(int i) {
    val.int_lit = i;
    type = tINT;
}
LiteralNode::LiteralNode(double d) {
    val.float_lit = d;
    type = tFLOAT;
}
LiteralNode::LiteralNode(string s) {
    val.string_lit = s;
    type = tSTRING;
}
LiteralNode::LiteralNode(bool b) {
    val.bool_lit = b;
    type = tBOOL;
}
LiteralNode::LiteralNode(char b) {
    val.byte_lit = b;
    type = tBYTE;
}

/* ArrayAccessNode */
ArrayAccessNode::ArrayAccessNode(ValueNode *val, ExpressionNode *exp) {
    vn = val;
    en = exp;
    type = val->type;
}

/* DatasetAccessNode */
DatasetAccessNode::DatasetAccessNode(ValueNode *v, IDNode *i) {
    vn = v;
    idn = i;
    type = v->type;
}

/* UnaryExpressionNode */
UnaryExpressionNode::UnaryExpressionNode(UnaryExpressionNode *u, string _op)
{
    op = str_to_op(_op);
    switch(op) {
        case MINUS:
            code = "-" + u->code;
            break;
        case SIZE:
            code = "sizeof( " + u->code + " )";
            break;
        case bNOT:
            code = "!" + u->code;
            break;
        default:
            break;
    }
    right_operand.u_exp = u;
}
UnaryExpressionNode::UnaryExpressionNode(ValueNode *v)
{
    op = NONE;
    right_operand.v_node = v;
    code = v->code;
}

/* BinaryExpressionNode */
BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op,BinaryExpressionNode *br) {
    left_operand.b_exp = bl;
    right_operand.b_exp = br;
    op = str_to_op(_op);
    code = gen_binary_code(bl->code, op, br->code); 
    left_is_binary = right_is_binary = true;
}
BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur) {
    left_operand.b_exp = bl;
    right_operand.u_exp = ur;
    op = str_to_op(_op);
    code = gen_binary_code(bl->code, op, ur->code); 
    left_is_binary = true;
    right_is_binary = false;
}


BinaryExpressionNode::BinaryExpressionNode(UnaryExpressionNode *ul) {
    left_operand.u_exp = ul;
    code = ul->code;
    op = NONE;
}

/* ExpressionNode */
ExpressionNode::ExpressionNode() { }
ExpressionNode::ExpressionNode(BinaryExpressionNode *b) {
    bin_exp = b;
    code = b->code;
    value = NULL;
}
ExpressionNode::ExpressionNode(BinaryExpressionNode *b, ValueNode *v) {
    bin_exp = b;
    code = v->code + "=" + b->code;
    value = v;
}
ExpressionNode::~ExpressionNode() {
}

/* DeclarativeStatementNode */
DeclarativeStatementNode::DeclarativeStatementNode(string _type, ExpressionNode *expression_node){
    type = str_to_type(_type);
    en = expression_node;

    transform(_type.begin(), _type.end(), _type.begin(), ::tolower);

    //TODO TYPE CONVERSIONS
    code = _type + " " + expression_node->code + ";\n"; 
}
DeclarativeStatementNode::DeclarativeStatementNode(ExpressionNode *expression_node){
    en = expression_node;
    code = expression_node->code + ";\n";
}

/* ConditionalStatementNode */
ConditionalStatementNode::ConditionalStatementNode(ExpressionNode *e, StatementListNode *s, StatementListNode *a) {
    condition = e;
    consequent = s;
    alternative = a;

    code = "if (" + e->code + ")" + s->code;

    if(a != nullptr)
        code += "else " + a->code;

}

/* JumpStatementNode */
JumpStatementNode::JumpStatementNode(string _type, ExpressionNode *expression_node){
    type = str_to_jump(_type);
    en = expression_node;
}
JumpStatementNode::JumpStatementNode(string _type){
    type = str_to_jump(_type);
}

/* LoopStatementNode */
LoopStatementNode::LoopStatementNode(ExpressionNode *init, ExpressionNode *cond, ExpressionNode *n, StatementListNode *stmts){
    initializer = init;
    condition = cond;
    next = n;
    statements = stmts;
}

/* StatementNode */
StatementNode::StatementNode(DeclarativeStatementNode *d){
    stmts.decl = d;
    code = d->code;
}
StatementNode::StatementNode(ConditionalStatementNode *c) {
    stmts.cond = c;
    code = c->code;
}
StatementNode::StatementNode(JumpStatementNode *j) {
    stmts.jump = j;
    code = j->code;
}
StatementNode::StatementNode(LoopStatementNode *l) {
    stmts.loop = l;
    code = l->code;
}

/* StatementListNode */
void StatementListNode::push_statement(StatementNode *s) {
    stmt_list.push_back(s);
    code = code + s->code;
}

/* FunctionNode */
FunctionNode::FunctionNode(string _type, IDNode *id_node, DeclArgsNode *decl_args_list, StatementListNode *stmt_list_n){
    type = str_to_type(_type);
    id = id_node;
    decl_args = decl_args_list;
    stmt_list = stmt_list_n;
    //TODO typing and symbol_table interactions
    
    transform(_type.begin(), _type.end(), _type.begin(), ::tolower);

    code = _type + " " + id_node->code + "(" + decl_args_list->code + ")" + stmt_list_n->code; 
}
