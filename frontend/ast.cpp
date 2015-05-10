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
    cout << type << endl;
    if (type.compare("int") == 0)
        return tINT;
    else if (type.compare("float") == 0)
        return tFLOAT;
    else if (type.compare("void") == 0)
        return tVOID;
    else if (type.compare("bool") == 0)
        return tBOOL;
    else if (type.compare("string") == 0)
        return tSTRING;
    else if (type.compare("byte") == 0)
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
        case tVOID:
            return "void";
        default:
            return "undefined type";
    }
}

void write_to_file(string filename, string code){

    ofstream file;
    file.open(filename);
    file << "#include \"link_files/ripple_header.h\"\n\n";
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
    link_code = VALUE_NODE(VARIABLE_NODE(code));
    linked_vars.push_back(new string(code));
    is_linkable = true;
}

ValueNode::ValueNode(LiteralNode *l) {
    val_type = LIT;
    val.lit_val = l;
    type = l->type;
    sym = l->sym;
    code = l->code;
    link_code = VALUE_NODE(LITERAL_NODE(code));
    is_linkable = true;
    array_length = l->array_length;
}

ValueNode::ValueNode(FunctionCallNode *f) {
    val_type = FUNC_CALL;
    val.function_call_val = f;
    type = f->type;
    sym = f->sym;
    code = f->code;
    is_linkable = false;
} 
ValueNode::ValueNode(ArrayAccessNode *a) {
    val_type = ARR_ACC;
    val.array_access_val = a;
    type = a->type;
    sym = a->sym;
    code = a->code;
    is_linkable = false;
}
ValueNode::ValueNode(DatasetAccessNode *d) {
    val_type = DS_ACC;
    val.dataset_access_val = d;
    type = d->type;
    sym = d->sym;
    code = d->code;
    is_linkable = false;
}
ValueNode::ValueNode(ExpressionNode *e) {
    val_type = EXPR;
    val.expression_val = e;
    type = e->type;
    sym = e->sym;
    code = "( " + e->code + " )";
    linked_vars.insert(linked_vars.end(), e->linked_vars.begin(), e->linked_vars.end());
    link_code = VALUE_NODE(e->link_code);
    is_linkable = true;
}
ValueNode::ValueNode(ArrayInitNode *a) {
    val.a_init = a;
    type = a->type;
    sym = tARR;
    code = "{ " + a->code + " }";
    array_length = a->has_elements ? a->array_length : -1;
    is_linkable = false;
}

void ValueNode::seppuku(){ 
    val.a_init->seppuku();
    delete this;
}

DatasetNode::DatasetNode(string s, DeclArgsNode *d) {
    name = s;
    decl_args = d;
    replace( decl_args->code.begin(), decl_args->code.end(), ',', ';');
    code = "struct " + s + "{\n" + decl_args->code + ";\n};";
}

void DatasetNode::seppuku(){ 
    decl_args->seppuku();
    delete this;
}

/* IDNode */
IDNode::IDNode(Entry *ent) {
    entry = ent;
    if (entry) {
        type = ent->type;
        code = ent->name;
        sym = ent->symbol_type;
    }
}

e_type IDNode::get_type() {
    return type;
}

string IDNode::get_name() {
    return entry->name;
}

void IDNode::seppuku(){ 
    delete this;
}

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

void FunctionCallNode::seppuku(){ 
    args_list->seppuku();
    delete this;
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
    has_elements = false;
    code = "";
    array_length = 0;
}

ArrayInitNode::ArrayInitNode(ExpressionNode *arg) {
    type = arg->type;
    sym = tARR;
    has_elements = true;
    args_list->push_back(arg);
    code = arg->code;
    array_length = 1;
}

void ArrayInitNode::add_arg(ExpressionNode *arg) {
    args_list->push_back(arg);
    sym = tARR;
    has_elements = true;
    if(type == 0 || (type == tINT && arg->type == tFLOAT)){
        type = arg->type;
    } else if(type == tFLOAT && arg->type == tINT){}
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

void ArrayInitNode::seppuku(){ 
    for(std::vector<ExpressionNode *>::iterator it = args_list->begin();
            it != args_list->end(); ++it)
        (*it)->seppuku();

    delete this;
}

/* ArgsNode */
ArgsNode::ArgsNode() {
    args_list = new vector<ExpressionNode *>(); 
    code = "";
}

ArgsNode::ArgsNode(ExpressionNode *arg) {
    if (arg->type == tNOTYPE) {
        error = true;
        cout << UNDECLARED_ERROR << endl;
    }
    args_list->push_back(arg);
    code = arg->code;
}

void ArgsNode::add_arg(ExpressionNode *arg) {
    args_list->push_back(arg);

    if (arg->type == tNOTYPE) {
        error = true;
        cout << UNDECLARED_ERROR << endl;
    }

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

void ArgsNode::seppuku(){ 
    for(std::vector<ExpressionNode *>::iterator it = args_list->begin();
            it != args_list->end(); ++it)
        (*it)->seppuku();
    delete this;
}

/* DeclArgsNode */
DeclArgsNode::DeclArgsNode() {
    code = "";
}

DeclArgsNode::DeclArgsNode(TypeNode *t, IDNode* arg) {
    decl_args_list.push_back(arg);
    arg->type = t->type;
    arg->entry->type = t->type;
    type = arg->type;
    code = type_to_str(type) + " " + arg->code;
}

void DeclArgsNode::add_arg(TypeNode *t, IDNode* arg) {
    decl_args_list.push_back(arg);
    arg->type = t->type;
    arg->entry->type = t->type;
    type = arg->type;
    code += ", " + type_to_str(type) + " " + arg->code;
}

vector<IDNode *>::iterator DeclArgsNode::begin() {
    return decl_args_list.begin();
}

vector<IDNode *>::iterator DeclArgsNode::end() {
    return decl_args_list.end();
}

list<e_type> *DeclArgsNode::to_enum_list() {
    list<e_type> *ret = new list<e_type>();
    for (vector<IDNode *>::iterator i = decl_args_list.begin(); i != decl_args_list.end(); i++) {
        ret->push_back((*i)->get_type());
    }
    return ret;
}

void DeclArgsNode::seppuku(){ 
    for(std::vector<IDNode *>::iterator it = decl_args_list.begin();
            it != decl_args_list.end(); ++it)
        (*it)->seppuku();
    delete this;
}

/* LiteralNode */
LiteralNode::LiteralNode(int i) {
    sym = tVAR;
    val.int_lit = i;
    array_length = i;
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

void LiteralNode::seppuku(){ 
    if(type == tSTRING)
        delete val.string_lit;
    delete this;
}

/* ArrayAccessNode */
ArrayAccessNode::ArrayAccessNode(ValueNode *val, ExpressionNode *exp) {
    value_node = val;
    en = exp;
    type = val->type;
    sym = val->sym;
    code = val->code + "[" + exp->code + "]";
}

void ArrayAccessNode::seppuku(){ 
    value_node->seppuku();
    en->seppuku();
    delete this;
}


/* DatasetAccessNode */
DatasetAccessNode::DatasetAccessNode(string c, string i) {
    Entry *entry = sym_table.get(c);
    if (!entry) {
        error = true;
        cout << LINE_ERR "use of undeclared variable" << c << endl;
    }

    Entry *member_entry = sym_table.get_dataset_member(entry->ds_name, i);
    if (!member_entry) {
        error = true;
        cout << LINE_ERR "dataset " << c << " of type " << entry->ds_name << "does not contain a member named " << i << endl;
    } else {
        cout << "here" << endl;
        entry = member_entry;
        type = member_entry->type;
        sym = member_entry->symbol_type;
        array_length = member_entry->array_length;
    }
}

void DatasetAccessNode::seppuku(){ 
    value_node->seppuku();
    delete this;
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
    link_code = UNARY_EXPRESSION(u->link_code, _op);
    linked_vars.insert(linked_vars.end(), u->linked_vars.begin(), u->linked_vars.end());
    is_linkable = u->is_linkable;
}

UnaryExpressionNode::UnaryExpressionNode(ValueNode *v){
    op = NONE;
    right_operand.v_node = v;
    array_length = v->array_length;
    type = v->type;
    sym = v->sym;
    code = v->code;
    link_code = UNARY_EXPRESSION(v->link_code);
    linked_vars.insert(linked_vars.end(), v->linked_vars.begin(), v->linked_vars.end());;
    is_linkable = v->is_linkable;
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
            if(child_type != tINT && child_type != tFLOAT){
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

void UnaryExpressionNode::seppuku(){ 
    if(op == NONE)
        right_operand.v_node->seppuku();
    else
        right_operand.u_exp->seppuku();
    delete this;
}


/* BinaryExpressionNode */
BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op, BinaryExpressionNode *br) {
    left_operand.b_exp = bl;
    right_operand.b_exp = br;
    left_is_binary = right_is_binary = true;

    op = str_to_op(_op);

    typecheck(bl, br, op);

    code = gen_binary_code(bl->code, op, br->code, bl->type, br->type);
    link_code = BINARY_EXPRESSION(bl->link_code, _op, br->link_code);
    linked_vars.insert(linked_vars.end(), bl->linked_vars.begin(), bl->linked_vars.end());
    linked_vars.insert(linked_vars.end(), br->linked_vars.begin(), br->linked_vars.end());
    is_linkable = bl->is_linkable && br->is_linkable;
}

BinaryExpressionNode::BinaryExpressionNode(BinaryExpressionNode *bl, string _op, UnaryExpressionNode *ur) {
    left_operand.b_exp = bl;
    right_operand.u_exp = ur;
    left_is_binary = true;
    right_is_binary = false;

    op = str_to_op(_op);
    typecheck(bl, ur, op);

    code = gen_binary_code(bl->code, op, ur->code, bl->type, ur->type);
    link_code = BINARY_EXPRESSION(bl->link_code, _op, ur->link_code);
    linked_vars.insert(linked_vars.end(), bl->linked_vars.begin(), bl->linked_vars.end());
    linked_vars.insert(linked_vars.end(), ur->linked_vars.begin(), ur->linked_vars.end());
    is_linkable = bl->is_linkable && ur->is_linkable;
}


BinaryExpressionNode::BinaryExpressionNode(UnaryExpressionNode *ul) {
    left_operand.u_exp = ul;
    left_is_binary = false;
    right_operand.b_exp = nullptr;
    type = ul->type;
    sym = ul->sym;
    code = ul->code;
    array_length = ul->array_length;
    op = NONE;

    link_code = BINARY_EXPRESSION(ul->link_code);
    is_linkable = ul->is_linkable;
    linked_vars.insert(linked_vars.end(), ul->linked_vars.begin(), ul->linked_vars.end());
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
        l_code = "std::to_string(" + l_code + ")";
    else if(l_type == tSTRING && r_type != tSTRING)
        r_code = "std::to_string(" + r_code + ")";

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
            code = "pow(" + l_code + ", " + r_code + ")";
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

ValueNode *BinaryExpressionNode::get_value_node() {
    if (op == NONE && left_operand.u_exp && left_operand.u_exp->op == NONE)
        return left_operand.u_exp->right_operand.v_node;
    return nullptr;
}

void BinaryExpressionNode::seppuku(){ 


    if(left_is_binary){
        left_operand.b_exp->seppuku();
    }
    else{
        left_operand.u_exp->seppuku();
    }

    if(op != NONE){
        if(right_is_binary){
            right_operand.b_exp->seppuku();
        }
        else {
            right_operand.u_exp->seppuku();
        }
    }

    delete this;
}

/* ExpressionNode */
ExpressionNode::ExpressionNode(BinaryExpressionNode *b) {

    ValueNode *v = b->get_value_node();
    if (v) {
        value = v;
        bin_exp = nullptr;
    } else {
        value = nullptr;
        bin_exp = b;
    }

    type = b->type;
    code = b->code;
    array_length = b->array_length;
    link_code = EXPRESSION_NODE(b->link_code);
    linked_vars = b->linked_vars;
    is_linkable = b->is_linkable;
}

ExpressionNode::ExpressionNode(BinaryExpressionNode *b, ValueNode *v) {
    bin_exp = b;
    value = v;
    typecheck(b, v);
    sym = b->sym;
    array_length = b->array_length;
    code = v->code + " = " + b->code;
}

ExpressionNode::~ExpressionNode() {}

void ExpressionNode::typecheck(BinaryExpressionNode *expression, ValueNode *value){

    if(value->sym != tVAR){
        error = true;
        cout << ASSIGN_ERR << endl;
    }

    type = expression->type;
}

void ExpressionNode::seppuku(){ 
    if(bin_exp != nullptr)
        bin_exp->seppuku();
    //if(value != nullptr)
    //    value->seppuku();
    delete this;
}

/* DeclarativeStatementNode */
DeclarativeStatementNode::DeclarativeStatementNode(TypeNode *t, ExpressionNode *expression_node){
    type = t->type;
    sym = t->sym;
    ds_name = t->ds_name;
    array_length = t->array_length;
    en = expression_node;

    if (!expression_node->value || expression_node->value->val_type != IDENT) {
        error = true;
        cout << INVALID_DECL_ERR << endl;
    }  
    typecheck();
    Entry *entry = sym_table.get(expression_node->value->code);
    switch(sym) {
        case tVAR:
            if (entry->type != tNOTYPE) {
                error = true;
                cout << VARIABLE_REDECL_ERR << endl;
            } else {
                entry->type = type;
            }
            code += type_to_str(type) + " " + expression_node->code + ";\n";
            break;
        case tARR:
            if (entry->type != tNOTYPE) {
                error = true;
                cout << VARIABLE_REDECL_ERR << endl;
            } else {
                entry->type = type;
            }
            if(expression_node->sym != tARR && expression_node->sym != tNOSTYPE) {
                error = true;
                cout << ARR_ASSIGN_ERR << endl;
            }

            if( array_length == -1 && !expression_node->bin_exp) {
                error = true;
                cout << ARR_UNKNOWN_INIT_ERR << endl;
            }

            if(array_length != -1 && array_length < expression_node->array_length) { 
                error = true;
                cout << ARR_SMALL_SIZE_ERR << endl;
            }

            if(!sym_table.add_array(expression_node->value->code, type, line_no, array_length)) {
                error = true;
                cout <<  VARIABLE_REDECL_ERR << endl;
            }

            code += type_to_str(type) + " " + expression_node->value->code + "[" + t->value->code + "]";
            if (expression_node->bin_exp) {
                code += "=" + expression_node->bin_exp->code;
            }
            code += ";\n";
            break;
        case tDSET:
            if (!sym_table.instantiate_dataset(expression_node->value->code, ds_name, line_no)) {
                error = true;
                cout << VARIABLE_REDECL_ERR << endl;
            }

            code += "struct ds " + expression_node->value->code + ";\n";
            break;
    }
}

DeclarativeStatementNode::DeclarativeStatementNode(ExpressionNode *expression_node){
    type = expression_node->type;
    en = expression_node;
    a_size = nullptr;
    code = expression_node->code + ";\n";

    ValueNode *val_node = expression_node->value;
    if (val_node) {
        if (val_node->val_type == IDENT) {
            Entry *entry = sym_table.get(val_node->code);
            if (entry) {
                if (entry->type == tNOTYPE) {
                    error = true;
                    cout << UNDECLARED_ERROR << endl;
                }
                if (entry->has_dependents) {
                    code += "linked_var::update_nonlinked_var(&" + entry->name + ");\n";
                }
            }
        }
    }
}

void DeclarativeStatementNode::typecheck() { 
    if (!en->bin_exp || type == tFLOAT && en->type == tINT){
    } else if (en->type != type){
        if(en->sym == tARR || sym == tARR){
            INVAL_ASSIGN_ERR(type_to_str(type) + "[]", type_to_str(en->type) + "[]");
        }
        else{
            INVAL_ASSIGN_ERR(type_to_str(type), type_to_str(en->type));
        }
        error = true;
    }
}


void DeclarativeStatementNode::seppuku(){ 
    if(a_size != nullptr)
        a_size->seppuku();
    en->seppuku();
    delete this;
}

/* TypeNode */
TypeNode::TypeNode(e_type t, string name){
    type = t;
    sym = tDSET;
    ds_name = name;

    value = nullptr;

}

TypeNode::TypeNode(e_type t, ValueNode *val) {
    type = t;
    value = val;

    if (type == tNOTYPE) {
        error = true;
        cout << UNKNOWN_TYPE_ERR << endl;
    }

    if(val){
        sym = tARR;
        array_length = val->array_length;
        if(val->type != tINT){
            cout << ARR_INT_SIZE_ERR << endl;
            error = true;
        }
    } else {
        sym = tVAR;
    }
}

/* ConditionalStatementNode */
ConditionalStatementNode::ConditionalStatementNode(ExpressionNode *e, StatementListNode *s, StatementListNode *a) {
    condition = e;
    consequent = s;
    alternative = a;

    if(e->type != tBOOL){
        error = true;
        cout << COND_STMT_ERR << endl;
    }

    code = "if (" + e->code + ")" + s->code;

    if(a != nullptr)
        code += "else " + a->code;
}

void ConditionalStatementNode::seppuku(){ 
    condition->seppuku();
    consequent->seppuku();
    if(alternative != nullptr)
        alternative->seppuku();
    delete this;
}


/* JumpStatementNode */
JumpStatementNode::JumpStatementNode(string _type, ExpressionNode *expression_node){
    type = str_to_jump(_type);
    en = expression_node;
    code = _type + " " + expression_node->code + ";\n";
}

JumpStatementNode::JumpStatementNode(string _type){
    type = str_to_jump(_type);
    en = nullptr;
    code = _type + ";\n";
}

void JumpStatementNode::seppuku(){ 
    if(en != nullptr)
        en->seppuku();
    delete this;
}


/* LoopStatementNode */
LoopStatementNode::LoopStatementNode(ExpressionNode *init, ExpressionNode *cond, ExpressionNode *n, StatementListNode *stmts){

    string init_code, cond_code, n_code;


    initializer = init;
    condition = cond;
    next = n;
    statements = stmts;

    if(cond->type != tBOOL){
        cout << LOOP_CONDITION_ERR << endl;
        error = true;
    }

    if(init != nullptr){
        init_code = init->code;
    } else {
        init_code = "";
    }

    if(cond != nullptr) {
        cond_code = cond->code;
    } else {
        cond_code = "";
    }

    if(n != nullptr) {
        n_code = n->code;
    } else {
        n_code = "";
    }

    code = "for (" + init_code + "; " + cond_code + "; " + n_code + ")" + stmts->code;
}

void LoopStatementNode::seppuku(){ 
    if(initializer != nullptr)
        initializer->seppuku();
    if(condition != nullptr)
        condition->seppuku();
    if(next != nullptr)
        next->seppuku();

    delete this;
}

LinkStatementNode::LinkStatementNode(IDNode *idn, ExpressionNode *expn){
    id_node = idn;
    expression_node = expn;
    if(!expression_node->is_linkable){
        error = true;
        cout << UNLINKABLE_EXPRESSION_ERR << endl;
    }

    if(expression_node->linked_vars.size() == 0){
        error = true;
        cout << UNLINKABLE_NO_VAR_ERR << endl;
    }

    code = "linked_var::register_cpp_var(&" + idn->code + ");\n";
    for(vector<string *>::iterator it = expression_node->linked_vars.begin(); it != expression_node->linked_vars.end(); it++) {
        code += "linked_var::register_cpp_var(&" + **it + ");\n";
        Entry *linked_entry = sym_table.get(**it);
        if (linked_entry) {
            linked_entry->has_dependents = true;
        } else {
            error = true;
            cout << UNDECLARED_ERROR << endl;
        }
    }
    code += "universal_linked_var_ptr = new linked_var (&" + idn->code + ", " + expression_node->link_code + ");\n";
}

LinkStatementNode::LinkStatementNode(IDNode *idn, ExpressionNode *expn, string func){
    id_node = idn;
    expression_node = expn;
    auxiliary = func;

    if(!expression_node->is_linkable){
        error = true;
        cout << UNLINKABLE_EXPRESSION_ERR << endl;
    }

    if(expression_node->linked_vars.size() == 0){
        error = true;
        cout << UNLINKABLE_NO_VAR_ERR << endl;
    }

    code = "linked_var::register_cpp_var(&" + idn->code + ");\n";
    for(vector<string *>::iterator it = expression_node->linked_vars.begin(); it != expression_node->linked_vars.end(); it++) {
        code += "linked_var::register_cpp_var(&" + **it + ");\n";
        Entry *linked_entry = sym_table.get(**it);
        if (linked_entry) {
            linked_entry->has_dependents = true;
        } else {
            error = true;
            cout << UNDECLARED_ERROR << endl;
        }
    }

    code += "universal_linked_var_ptr = new linked_var (&" + idn->code + ", " + expression_node->link_code + ");\n";
    Entry *entry = sym_table.get(auxiliary);
    if (!entry) {
        cout << UNDECLARED_ERROR << endl;
    } else {
        if (entry->symbol_type != tFUNC || entry->type != tVOID) {
            error = true;
            cout << INVAL_FUNC_CALL_ERR << endl;
        } else  {
            if (entry->args->size() != 1 || entry->args->front() != id_node->type) {
                error = true;
                cout << INVAL_FUNC_ARGS_ERR << endl;
            } else {
                code += "universal_linked_var_ptr->assign_aux_fn((void *)" + auxiliary + ");";
            }
        }
    }
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

void StatementNode::seppuku(){ 
    stmts.decl->seppuku();
    delete this;
}

StatementNode::StatementNode(LinkStatementNode *l){
    stmts.link = l;
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

void StatementListNode::seppuku(){ 
    for(std::vector<StatementNode *>::iterator it = stmt_list->begin();
            it != stmt_list->end(); ++it)
        (*it)->seppuku();

    delete this;
}

/* FunctionNode */
FunctionNode::FunctionNode(TypeNode *_type, string id_node, DeclArgsNode *decl_args_list, StatementListNode *stmt_list_n){
    if (_type->sym != tVAR) {
        error = true;
        cout << FUNCTION_BASIC_TYPE_ERR << endl;
    }
    id = id_node;
    decl_args = decl_args_list;
    stmt_list = stmt_list_n;
    type = _type->type;

    if (id.compare("main") == 0) {
        code = "int " + id + "(" + decl_args_list->code + ")" + stmt_list_n->code; 
    } else {
        code = type_to_str(type) + " " + id + "(" + decl_args_list->code + ")" + stmt_list_n->code;
    }
}

void FunctionNode::seppuku(){ 
    decl_args->seppuku();
    stmt_list->seppuku();
    delete this;
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

void ProgramSectionNode::seppuku(){ 
    contents.function->seppuku();
    delete this;
}

/* ProgramNode */
ProgramNode::ProgramNode() {
    code = "";
}

void ProgramNode::add_section(ProgramSectionNode *p) {
    code += p->code;
    //p->seppuku();
}
