#ifndef INCLUDED_PARSE_ERRORS
#define INCLUDED_PARSE_ERRORS

#define LINE_ERR "Error on line number " + to_string(line_no) + ": " <<

#define UNARY_STRING_CAST_ERR LINE_ERR "cannot cast string to bool, int or float"
#define INVAL_UNARY_NOT_ERR LINE_ERR "unary - not supported between provided operands"
#define INVAL_UNARY_MINUS_ERR LINE_ERR "unary - not supported between provided operands"

#define INVAL_BINARY_DERIVED_ERR LINE_ERR "binary operators are not valid between derived types"

#define INVAL_BINARY_PLUS_ERR LINE_ERR "binary + not supported between provided operands"
#define INVAL_BINARY_MINUS_ERR LINE_ERR "binary - not supported between provided operands"
#define INVAL_BINARY_TIMES_ERR LINE_ERR "binary * not supported between provided operands"
#define INVAL_BINARY_DIV_ERR LINE_ERR "binary // not supported between provided operands"
#define INVAL_BINARY_EXP_ERR LINE_ERR "binary ^ not supported between provided operands"
#define INVAL_BINARY_FLDIV_ERR LINE_ERR "binary / not supported between provided operands"
#define INVAL_BINARY_MOD_ERR LINE_ERR "binary % not supported between provided operands"
#define INVAL_BINARY_EQ_ERR LINE_ERR "binary == not supported between provided operands"
#define INVAL_BINARY_NE_ERR LINE_ERR "binary != not supported between provided operands"
#define INVAL_BINARY_GT_ERR LINE_ERR "binary > not supported between provided operands"
#define INVAL_BINARY_LT_ERR LINE_ERR "binary < not supported between provided operands"
#define INVAL_BINARY_GE_ERR LINE_ERR "binary >= not supported between provided operands"
#define INVAL_BINARY_LE_ERR LINE_ERR "binary <= not supported between provided operands"
#define INVAL_BINARY_AND_ERR LINE_ERR "binary and not supported between provided operands"
#define INVAL_BINARY_OR_ERR LINE_ERR "binary or not supported between provided operands"
#define INVAL_FUNC_CALL_ERR LINE_ERR "function call error"
#define LOOP_CONDITION_ERR LINE_ERR "loop condition variable must be of type bool"
#define UNKNOWN_TYPE_ERR LINE_ERR "unknown type error"
#define FUNCTION_BASIC_TYPE_ERR LINE_ERR "functions can only return primitive types"
#define RETURN_TYPE_ERROR LINE_ERR "return type does not match function type"

#define INVALID_DECL_ERR LINE_ERR "all declarations must have have an associated variable"
#define VARIABLE_REDECL_ERR LINE_ERR "variable being declared is a redeclaration of a previously declared variable"
#define UNDECLARED_ERROR LINE_ERR "use of undeclared identifier"

#define INVALID_FILE_SR_TYPES_ERR LINE_ERR "invlaid types for file_stream"
#define INVALID_KEYBOARD_SR_ERR LINE_ERR "incorrect number of arguments for keyboard_stream error"
#define INVALID_FILE_SR_ERR LINE_ERR "incorrect number of arguments for file_stream"
#define INVALID_WEB_SR_ERR LINE_ERR "incorrect number of arguments for web_stream"
#define INVALID_WEB_SR_TYPES_ERR LINE_ERR "invalid types for web_stream"

#define ARR_ELEMENT_TYPE_ERR LINE_ERR "all elements in an array initialization must have the same type"
#define ARR_UNARY_MINUS_ERR LINE_ERR "cannot perform negation on arrays"
#define ARR_UNARY_NOT_ERR LINE_ERR "cannot perform boolean not on arrays"
#define ARR_UNARY_CAST_ERR LINE_ERR "cannot cast array to any other type type"
#define ARR_BINEXP_ERR LINE_ERR "cannot perform binary operations on arrays"
#define ARR_VAR_ASSIGN_ERR LINE_ERR "cannot assign array to non-array variable"
#define ARR_INT_SIZE_ERR LINE_ERR "array initialization size must be int"
#define ARR_UNKNOWN_SIZE_ERR LINE_ERR "variable size array cannot be initialized"
#define ARR_UNKNOWN_INIT_ERR LINE_ERR "cannot create an array of unknown size without initialization"
#define ARR_SMALL_SIZE_ERR LINE_ERR "size of array declared is too small"
#define ARR_ASSIGN_ERR LINE_ERR "can't assign array to non-array variable"

#define FINAL_MUST_INITIALIZE LINE_ERR "must initialize a final variable"
#define FINAL_REDECL_ERR LINE_ERR "cannot change a final variable"
#define UNLINKABLE_NO_VAR_ERR LINE_ERR "linked expression must have variables"
#define UNLINKABLE_EXPRESSION_ERR LINE_ERR "expression provided cannot be linked"
#define INVAL_FUNC_ARGS_ERR LINE_ERR \
                            "an auxiliary function may only have one argument of the same type as the linked variable"
#define NOT_A_FUNC_ERR LINE_ERR "provided identifier is not callable"
#define COND_STMT_ERR LINE_ERR "expression in if statement must be of type boolean"
//#define LOOP_CONDITION_ERR LINE_ERR "condition expression in loop must be of type boolean"

#define ASSIGN_ERR LINE_ERR "left operand of assignment expression must be a variable"

#define INVAL_ASSIGN_ERR(val_type, expression_type) { cout << LINE_ERR \
    "invalid assignment between operands of type " <<  \
    val_type << " and " << expression_type << endl; }

#define ERROR "error"
#define MAIN_FUNC_ERROR "All ripple programs need a main function."
#define COMPILE_ERR "Unable to complete compilation due to errors in code. Get good."

#endif