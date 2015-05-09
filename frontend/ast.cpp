#include "ast.h"
#include <string>
#include "../misc/debug_tools.h"

enum e_op str_to_op(const std::string op_string) {
    if(op_string.compare("+") == 0)
        return PLUS;
    else if (op_string.compare("-") == 0)
        return MINUS;
    else if (op_string.compare("*") == 0)
        return TIMES;
    else if (op_string.compare("/") == 0)
        return DIV;
    else if (op_string.compare("%") == 0)
        return MOD;
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
    if (type.compare("return") == 0)
        return tRETURN;
    else if (type.compare("break") == 0)
        return tBREAK;
    else if (type.compare("continue") == 0)
        return tCONTINUE;
}

string type_to_str(e_type type){
    switch(type){
        case tBYTE:
            return "byte";
        case tBOOL:
            return "bool";
        case tINT:
            return "int";
        case tFLOAT:
            return "float";
        case tSTRING:
            return "string";
        default:
            return "undefined type";
    }
}

void write_to_file(string filename, string code){

    ofstream file;
    file.open(filename);
    file << "#include \"link_files/ripple_header.h\"\n";
    file << code;
    file.close();
}


/* Node */
e_type Node::get_type() {
    return this->type;
}

bool Node::is_bool() {
    return (type == tBOOL);
}

bool Node::is_number() {
    return (type == tINT || type == tFLOAT);
}

bool Node::is_string() {
    return (type == tSTRING);
}

/* ValueNode */
ValueNode::ValueNode(IDNode *i) {
    val_type = IDENT;
    val.id_val = i;
    type = i->type;
    sym = i->sym;
    code = i->code;
}
ValueNode::ValueNode(LiteralNode *l) {
    val_type = LIT;
    val.lit_val = l;
    type = l->type;
    sym = l->sym;
    code = l->code;
}
ValueNode::ValueNode(FunctionCallNode *f) {
    val_type = FUNC_CALL;
    val.function_call_val = f;
    type = f->type;
    sym = f->sym;
    code = f->code;
} 
ValueNode::ValueNode(ArrayAccessNode *a) {
    val_type = ARR_ACC;
    val.array_access_val = a;
    type = a->type;
    sym = a->sym;
    code = a->code;
}
ValueNode::ValueNode(DatasetAccessNode *d) {
    val_type = DS_ACC;
    val.dataset_access_val = d;
    type = d->type;
    sym = d->sym;
    code = d->code;
}
ValueNode::ValueNode(ExpressionNode *e) {
    val_type = EXPR;
    val.expression_val = e;
    type = e->type;
    sym = e->sym;
    code = "( " + e->code + " )";
}
ValueNode::ValueNode(ArrayInitNode *a) {
    val.a_init = a;
    type = a->type;
    sym = tARR;
    code = "{ " + a->code + " }";
    array_length = a->array_length;
}


/* IDNode */
IDNode::IDNode(Entry *ent) {
    entry = ent;
    if (ent) { // is there a better way to deal with
        // undeclared identifiers?
        type = ent->type;
        code = ent->name;
        sym = ent->symbol_type;
    }
}
IDNode::~IDNode() { }


/* FunctionCallNode */
FunctionCallNode::FunctionCallNode(string f, ArgsNode *a) {
    func_id = f;
    args_list = a;
    sym = tFUNC;

    typecheck();

    if(IS_STD_RPL_FUNCTION(func_id)){
        code = generate_std_rpl_function();
    } else {
        code = f + "( " + a->code + " )";
    }   
}

FunctionCallNode::FunctionCallNode(string f) {
    func_id = f;
    args_list = new ArgsNode();
    sym = tFUNC;

    typecheck();

    if(IS_STD_RPL_FUNCTION(func_id)){
        code = generate_std_rpl_function();
    } else {
        code = f + "()";
    }   
}

void FunctionCallNode::typecheck() {
    Entry *entry = sym_table.get(func_id);
    if (entry) {
        if (entry->symbol_type != tFUNC) {
            error = true;
            cout << NOT_A_FUNC_ERR << endl;
        } else if (entry->args) {
            if (*entry->args != *args_list->to_enum_list()) {
                error = true;
                cout << INVAL_FUNC_CALL_ERR << endl;
            }
        }
        type = entry->type;
    } else {
        error = true;
        cout << "use of undeclared function " << func_id << endl;
    }
}

string FunctionCallNode::generate_std_rpl_function(){
    string func_name = func_id;
    string code;
    if (func_name.compare(RPL_STD_OUTPUT_FUNCTION) == 0){
        code = "std::cout << ";
        for(std::vector<ExpressionNode *>::iterator it = args_list->args_list->begin(); it != args_list->args_list->end(); ++it) {
            code += (*it)->code + " << \" \" << ";
        }
        code += "std::endl";
    } else if (func_name.compare(RPL_STD_INPUT_FUNCTION) == 0){

    } else if (func_name.compare(RPL_STD_OPEN_FUNCTION) == 0){

    } else if (func_name.compare(RPL_STD_CLOSE_FUNCTION) == 0){

    } else if (func_name.compare(RPL_STD_READ_FUNCTION) == 0){

    }
    return code;
}

/* ArrayInitNode */
ArrayInitNode::ArrayInitNode() {
    args_list = new vector<ExpressionNode *>(); 
    sym = tARR;
    code = "";
    array_length = 0;
}

ArrayInitNode::ArrayInitNode(ExpressionNode *arg) {
    type = arg->type;
    sym = tARR;

    args_list->push_back(arg);
    code = arg->code;
    array_length = 1;
}

void ArrayInitNode::add_arg(ExpressionNode *arg) {
    args_list->push_back(arg);
    sym = tARR;

    if(type == 0){
        type = arg->type;
    }
    else if(arg->type != type){
        error = true;
        cout << ARR_ELEMENT_TYPE_ERR << endl;
    }
    if(code.compare("") == 0)
        code += arg->code;
    else
        code += ", " + arg->code;

    array_length++;
}

/* ArgsNode */
ArgsNode::ArgsNode() {
    args_list = new vector<ExpressionNode *>(); 
    code = "";
}

ArgsNode::ArgsNode(ExpressionNode *arg) {
    args_list->push_back(arg);
    code = arg->code;
}

void ArgsNode::add_arg(ExpressionNode *arg) {
    args_list->push_back(arg);

    if(code.compare("") == 0)
        code += arg->code;
    else
        code += ", " + arg->code;
}

list<e_type> *ArgsNode::to_enum_list() {
    list<e_type> *ret = new list<e_type>();
    for (vector<ExpressionNode *>::iterator i = args_list->begin(); i != args_list->end(); i++) {
        ret->push_back((*i)->type);
    }
    return ret;
}

/* DeclArgsNode */
DeclArgsNode::DeclArgsNode() {
    code = "";
}

DeclArgsNode::DeclArgsNode(string t, IDNode* arg) {
    decl_args_list.push_back(arg);
    arg->type = str_to_type(t);
    arg->entry->type = str_to_type(t);
    type = arg->type;
    code = type_to_str(type) + " " + arg->code;
}

void DeclArgsNode::add_arg(string t, IDNode* arg) {
    decl_args_list.push_back(arg);
    arg->type = str_to_type(t);
    arg->entry->type = str_to_type(t);
    type = arg->type;
    code += ", " + type_to_str(type) + " " + arg->code;
}

vector<IDNode *>::iterator DeclArgsNode::begin() {
    return decl_args_list.begin();
}

vector<IDNode *>::iterator DeclArgsNode::end() {
    return decl_args_list.end();
}

/* LiteralNode */
LiteralNode::LiteralNode(int i) {
    sym = tVAR;
    val.int_lit = i;
    type = tINT;
}

LiteralNode::LiteralNode(double d) {
    sym = tVAR;
    val.float_lit = d;
    type = tFLOAT;
}

LiteralNode::LiteralNode(string *s) {
    sym = tVAR;
    val.string_lit = s;
    type = tSTRING;
}

LiteralNode::LiteralNode(bool b) {
    sym = tVAR;
    val.bool_lit = b;
    type = tBOOL;
}

LiteralNode::LiteralNode(char b) {
    sym = tVAR;
    val.byte_lit = b;
    type = tBYTE;
}


/* ArrayAccessNode */
ArrayAccessNode::ArrayAccessNode(ValueNode *val, ExpressionNode *exp) {
    value_node = val;
    en = exp;
    type = val->type;
    sym = val->sym;
}


/* DatasetAccessNode */
DatasetAccessNode::DatasetAccessNode(ValueNode *val, string i) {
    value_node = val;
    id = i;
    type = val->type;
    sym = tDSET;
    array_length = val->array_length;
}

/* UnaryExpressionNode */
UnaryExpressionNode::UnaryExpressionNode(UnaryExpressionNode *u, string _op) {

    right_operand.u_exp = u;
    array_length = u->array_length;
    op = str_to_op(_op);
    sym = u->sym;
    typecheck(op);
    switch(op) {
        case MINUS:
            code = "-" + u->code;
            break;
        case SIZE:
            if(sym == tARR){
                code = "sizeof( " + u->code + " ) / sizeof( " + type_to_str(u->type) + " )";
            } else {
                code = "sizeof( " + u->code + " )";
            }
            break;
        case bNOT:
            code = "!" + u->code;
            break;
        default:
            break;
    }
}

UnaryExpressionNode::UnaryExpressionNode(ValueNode *v){
    op = NONE;
    right_operand.v_node = v;
    array_length = v->array_length;
    type = v->type;
    sym = v->sym;
    code = v->code;
}

void UnaryExpressionNode::typecheck(e_op op){

    e_type child_type = right_operand.u_exp->type;

    if(sym == tARR && op != SIZE){
        error = true;
        if(op == bNOT)
            cout << ARR_UNARY_NOT_ERR << endl;
        else if(op == MINUS)
            cout << ARR_UNARY_MINUS_ERR << endl;
        return;
    }

    switch(op){
        case bNOT:
            if(child_type != tBOOL){
                cout << INVAL_UNARY_NOT_ERR << endl;
                error = true;
            }
            else
                type = tBOOL;
            break;
        case MINUS:
            if(child_type != tINT || child_type != tFLOAT){
                cout << INVAL_UNARY_MINUS_ERR << endl;
                error = true;
            }
            else
                type = child_type;
            break;
        default:
            type = child_type;
    }
}


/* BinaryExpressionNode */
BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op, BinaryExpressionNode *br) {
    left_operand.b_exp = bl;
    right_operand.b_exp = br;
    op = str_to_op(_op);
    typecheck(bl, br, op);
    code = gen_binary_code(bl->code, op, br->code, bl->type, br->type); 
    left_is_binary = right_is_binary = true;
}

BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur) {
    left_operand.b_exp = bl;
    right_operand.u_exp = ur;
    op = str_to_op(_op);
    typecheck(bl, ur, op);
    code = gen_binary_code(bl->code, op, ur->code, bl->type, ur->type);
    left_is_binary = true;
    right_is_binary = false;
}


BinaryExpressionNode::BinaryExpressionNode(UnaryExpressionNode *ul) {
    left_operand.u_exp = ul;
    left_is_binary = false;
    type = ul->type;
    sym = ul->sym;
    code = ul->code;
    array_length = ul->array_length;
    op = NONE;
}

void BinaryExpressionNode::typecheck(Node *left, Node *right, e_op op){

    if(left->sym == tARR || right->sym == tARR){
        error = true;
        cout << ARR_BINEXP_ERR << endl;
    }

    if((left->is_string() || right->is_string()) && op == PLUS) {
        type = tSTRING;
        return;
    }

    if (op == PLUS || op == MINUS || op == TIMES || op == DIV || op == EXP) {

        if (left->is_number() && right->is_number())
            if (left->type == tFLOAT || right->type == tFLOAT)
                type = tFLOAT;
            else
                type = tINT;
        else
            switch(op){
                case PLUS:
                    cout << INVAL_BINARY_PLUS_ERR << endl;
                    error = true;
                    break;
                case MINUS:
                    cout << INVAL_BINARY_MINUS_ERR << endl;
                    error = true;
                    break;
                case TIMES:
                    cout << INVAL_BINARY_TIMES_ERR << endl;
                    error = true;
                    break;
                case DIV:
                    cout << INVAL_BINARY_DIV_ERR << endl;
                    error = true;
                    break;
                case EXP:
                    cout << INVAL_BINARY_EXP_ERR << endl;
                    error = true;
                    break;
                default:
                    cout << ERROR << endl;
                    error = true;
            }

    } else if (op == FLDIV) {

        if (left->is_number() && right->is_number())
            type = tFLOAT;
        else{
            cout << INVAL_BINARY_FLDIV_ERR << endl;
            error = true;
        }

    } else if (op == MOD) {

        if (left->is_number() && right->is_number()
            && left->type == tINT && right->type == tINT){
            type = tINT;
        } else {
            error = true;
            cout << INVAL_BINARY_MOD_ERR << endl;
        }

    } else if (op == EQ || op == NE || op == GT ||
            op == LT || op == GE || op == LE) {

        if (left->is_number() && right->is_number())
            type = tBOOL;
        else
            switch(op){
                case EQ:
                    cout << INVAL_BINARY_EQ_ERR << endl;
                    error = true;
                    break;
                case NE:
                    cout << INVAL_BINARY_NE_ERR << endl;
                    error = true;
                    break;
                case GT:
                    cout << INVAL_BINARY_GT_ERR << endl;
                    error = true;
                    break;
                case LT:
                    cout << INVAL_BINARY_LT_ERR << endl;
                    error = true;
                    break;
                case GE:
                    cout << INVAL_BINARY_GE_ERR << endl;
                    error = true;
                    break;
                case LE:
                    cout << INVAL_BINARY_LE_ERR << endl;
                    error = true;
                    break;
                default:
                    cout << ERROR << endl;
                    error = true;
            }

    } else if (op == bAND || bOR) {
        if (left->is_bool() && right->is_bool())
            type = tBOOL;
        else
            switch(op){
                case bAND:
                    cout << INVAL_BINARY_AND_ERR << endl;
                    error = true;
                    break;
                case bOR:
                    cout << INVAL_BINARY_OR_ERR << endl;
                    error = true;
                    break;
                default:
                    cout << ERROR << endl;
                    error = true;
            }
    }

}

string BinaryExpressionNode::gen_binary_code(string l_code, enum e_op op, string r_code, e_type l_type, e_type r_type){
    string code;

    if(r_type == tSTRING && l_type != tSTRING)
        l_code = "to_string(" + l_code + ")";
    else if(l_type == tSTRING && r_type != tSTRING)
        r_code = "to_string(" + r_code + ")";

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
        case MOD:
            code = l_code + " % " + r_code;
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


/* ExpressionNode */
ExpressionNode::ExpressionNode(BinaryExpressionNode *b) {
    ValueNode *v = b->get_value_node();
    if (v) {
        value = v;
    } else {
        bin_exp = b;
    }
    type = b->type;
    code = b->code;
    array_length = b->array_length;
}

ValueNode *BinaryExpressionNode::get_value_node() {
    if (op == NONE && left_operand.u_exp && left_operand.u_exp->op == NONE)
        return left_operand.u_exp->right_operand.v_node;
    return nullptr;
}

ExpressionNode::ExpressionNode(BinaryExpressionNode *b, ValueNode *v) {
    bin_exp = b;
    typecheck(b, v);
    sym = b->sym;
    array_length = b->array_length;
    code = v->code + " = " + b->code;
    value = v;
}

ExpressionNode::~ExpressionNode() {}

void ExpressionNode::typecheck(BinaryExpressionNode *expression, ValueNode *value){

    if(value->sym != tVAR){
        error = true;
        cout << ASSIGN_ERR << endl;
    }

    if (expression->type == value->type){
        type = value->type;
    }
    else if (value->type == tFLOAT){
        if(expression->type == tINT)
            type = tFLOAT;
    }
    else{
        INVAL_ASSIGN_ERR(type_to_str(value->type), type_to_str(expression->type));
        error = true;
    }
}

/* DeclarativeStatementNode */
DeclarativeStatementNode::DeclarativeStatementNode(string _type, ValueNode *arr_size, ExpressionNode *expression_node){
    type = str_to_type(_type);
    a_size = arr_size;
    en = expression_node;
    transform(_type.begin(), _type.end(), _type.begin(), ::tolower);

    code = _type + " ";
    if(a_size == nullptr){
        if(expression_node->sym == tARR){
            cout << ARR_VAR_ASSIGN_ERR << endl;
            error = true;
        } else {
            code += expression_node->code + ";\n"; 
        }
    } else {
        
        if(a_size->type != tINT){
            error = true;
            cout << ARR_INT_SIZE_ERR << endl;
        }

        if(a_size->sym != tVAR){
            error = true;
            cout << ARR_UNKNOWN_SIZE_ERR << endl;
        }

        if(arr_size->val.lit_val->val.int_lit != -1 && 
            arr_size->val.lit_val->val.int_lit < expression_node->array_length) {
            
            error = true;
            cout << ARR_SMALL_SIZE_ERR << endl;
        }

        if(expression_node->sym != tARR){
            error = true;
            cout << ARR_ASSIGN_ERR << endl;

        }

        if(expression_node->value)
            code += expression_node->value->code + "[" + arr_size->code + "] = " + expression_node->bin_exp->code + ";\n";
        else 
            code += expression_node->bin_exp->code + "[" + arr_size->code + "];\n";
        
    }

    if(arr_size){
        if(expression_node->value)
            expression_node->value->val.id_val->entry->symbol_type = tARR;
        else
            expression_node->bin_exp->left_operand.u_exp->right_operand.v_node->val.id_val->entry->symbol_type = tARR;
    }
}

DeclarativeStatementNode::DeclarativeStatementNode(ExpressionNode *expression_node){
    type = expression_node->type;
    en = expression_node;
    code = expression_node->code + ";\n";
}


/* ConditionalStatementNode */
ConditionalStatementNode::ConditionalStatementNode(ExpressionNode *e, StatementListNode *s, StatementListNode *a) {
    condition = e;
    consequent = s;
    alternative = a;

    // TYPE CHECK
    code = "if (" + e->code + ")" + s->code;

    if(a != nullptr)
        code += "else " + a->code;
}


/* JumpStatementNode */
JumpStatementNode::JumpStatementNode(string _type, ExpressionNode *expression_node){
    type = str_to_jump(_type);
    en = expression_node;
    code = _type + " " + expression_node->code + ";\n";
}

JumpStatementNode::JumpStatementNode(string _type){
    type = str_to_jump(_type);
    code = _type + ";\n";
}


/* LoopStatementNode */
LoopStatementNode::LoopStatementNode(ExpressionNode *init, ExpressionNode *cond, ExpressionNode *n, StatementListNode *stmts){
    initializer = init;
    condition = cond;
    next = n;
    statements = stmts;
    if(cond->type != tBOOL){
        cout << LOOP_CONDITION_ERR << endl;
        error = true;
    }

    string init_code, cond_code, n_code;
    if(init != nullptr)
        init_code = init->code;
    else
        init_code = "";

    if(cond != nullptr)
        cond_code = init->code;
    else
        cond_code = "";

    if(n != nullptr)
        n_code = init->code;
    else
        n_code = "";

    code = "for (" + init_code + ", " + cond_code + ", " + n_code + ")" + stmts->code;
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
StatementListNode::StatementListNode() {
    stmt_list = new vector<StatementNode *>();
    st_node = nullptr;
}

StatementListNode::StatementListNode(SymbolTableNode *s) {
    stmt_list = new vector<StatementNode *>();
    st_node = s;
}

void StatementListNode::push_statement(StatementNode *s) {
    stmt_list->push_back(s);
    code = code + s->code;
}

/* FunctionNode */
FunctionNode::FunctionNode(string _type, string id_node, DeclArgsNode *decl_args_list, StatementListNode *stmt_list_n){
    type = str_to_type(_type);
    id = id_node;
    decl_args = decl_args_list;
    stmt_list = stmt_list_n;

    transform(_type.begin(), _type.end(), _type.begin(), ::tolower);

    if (id.compare("main") == 0) {
        code = "int " + id + "(" + decl_args_list->code + ")" + stmt_list_n->code; 
    } else {
        code = _type + " " + id + "(" + decl_args_list->code + ")" + stmt_list_n->code;
    }
}

e_type IDNode::get_type() {
    return type;
}

string IDNode::get_name() {
    return entry->name;
}

list<e_type> *DeclArgsNode::to_enum_list() {
    list<e_type> *ret = new list<e_type>();
    for (vector<IDNode *>::iterator i = decl_args_list.begin(); i != decl_args_list.end(); i++) {
        ret->push_back((*i)->get_type());
    }
    return ret;
}

DatasetNode::DatasetNode(string s, DeclArgsNode *d) {
    name = s;
    decl_args = d; 
}

/* ProgramSectionNode */
ProgramSectionNode::ProgramSectionNode(FunctionNode *f) {
    contents.function = f;
    code = f->code;
}

ProgramSectionNode::ProgramSectionNode(DatasetNode *d) {
    contents.dataset = d;
    code = d->code;
}

/* ProgramNode */
ProgramNode::ProgramNode() {
    code = "";
}

void ProgramNode::add_section(ProgramSectionNode *p) {
    code += p->code;
}
