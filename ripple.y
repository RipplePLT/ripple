%{
#include <stdio.h>

/***************
    KEYWORDS 
***************/
#define IF 1
#define ELSE 2
#define FOR 3
#define WHILE 4
#define LINK 5
#define IMPORT 6
#define FINAL 7
#define RETURN 8
#define CONTINUE 9
#define BREAK 10

/***************
      TYPES 
***************/
#define TYPE 11
#define BOOL 12
#define BYTE 13
#define INT 14
#define FLOAT 15
#define STRING 16
#define DATASET 17
#define VOID 18

/***************
       OP
***************/
#define EQ 21
#define NE 22
#define LT 23
#define LE 24
#define GT 25
#define GE 26

#define PLUS 27
#define MINUS 28
#define TIMES 29
#define DIV 30
#define MOD 31
#define FLDIV 32
#define EXP 33
#define AT 34

#define AND 35
#define OR 36
#define NOT 37

/***************
    VARIABLES 
***************/
#define ID 41
#define NUM 42
#define LITERAL 43
#define TRUE 44
#define FALSE 45

/***************
    LITERALS
***************/
#define ARROW 51
#define ASSIGN 52
#define SEMICOL 53
#define ACCESS 54

#define L_PAREN 55
#define R_PAREN 56
#define L_CURLY 57
#define R_CURLY 58
#define L_BRACKET 59
#define R_BRACKET 60
#define COMMA 61


int yylval;
%}


%%

program_declarations : program_declarations program_declaration
					 | 
					 ;

program_declaration : import_statement
					| final_declaration
					| dataset_declaration
					| function
					;

import_statement : IMPORT LITERAL SEMICOLON
				 ;

dataset_declaration : DATASET ID L_CURLY declaration_list R_CURLY
					;

final_declaration : FINAL declaration_statement
				  ;

function : LINK declaration declaration_args L_CURLY statement_list R_CURLY

declaration_list : declaration SEMICOLON declaration_list
				 |
				 ;

declaration : TYPE ID
			| ID
			| TYPE L_BRACKET expression R_BRACKET
			| TYPE L_BRACKET R_BRACKET
			;

declaration_args : L_PAREN declaration declaration_arg_list R_PAREN
				 | L_PAREN R_PAREN
				 ;

declaration_arg_list : COMMA declaration declaration_arg_list
					 | 
					 ;

statement_list : statement_list statement_block 
			   |
			   ;

/******************
    STATEMENTS
*******************/

statement : conditional_statement 
		  | loop_statement 
		  | link_statement 
		  | declarative_statement 
		  | jump_statement
		  ;

conditional_statement : IF L_PAREN expression R_PAREN statement_block else_statement
					  ;

else_statement : ELSE statement_block 
			  |
			  ;

loop_statement : WHILE L_PAREN expression R_PAREN statement_block 
               | FOR L_PAREN declarative_statement expression SEMICOLON expression R_PAREN statement_block
               ;

link_statement : LINK L_PAREN declaration link_stream R_PAREN function_call SEMICOLON
			   : LINK L_PAREN declaration link_stream R_PAREN SEMICOLON
			   ;

link_stream : ARROW stream_reader
            | ARROW expression
            ;

stream_reader : READER_NAME L_PAREN function_call_args R_PAREN

declarative_statement : declaration ASSIGN expression SEMICOLON
                      | expression SEMICOLON
                      | declaration SEMICOLON
                      ;

declarative_statement : declaration EQUALS expression SEMICOLON
                      | expression SEMICOLON
                      | declaration SEMICOLON
                      ;

statement_block : statement_list SEMICOLON
                | expression SEMICOLON
                | declaration SEMICOLON
                ;

jump_statement : RETURN expression SEMICOLON
               | CONTINUE SEMICOLON
               | BREAK SEMICOLON
               ;

/*******************
    Expressions
*******************/

expression : expression OR and_expression
           | and_expression
           ;

and_expression : and_expression AND eq_expression
               | eq_expression
               ;

eq_expression : eq_expression EQ rel_expression
              | eq_expression NE rel_expression
              | rel_expression
              ;

rel_expression : rel_expression LT plus_expression
               | rel_expression LE plus_expression
               | rel_expression GE plus_expression
               | rel_expression GT plus_expression
               | plus_expression
               ;

plus_expression : plus_expression PLUS mult_expression
                | plus_expression MINUS mult_expression
                | mult_expression
                ;

mult_expression : mult_expression TIMES unary_expression
                | mult_expression DIV unary_expression
                | mult_expression FLDIV unary_expression
                | mult_expression MOD unary_expression
                | unary_expression
                ;

unary_expression : NOT unary_expression
                 | MINUS unary_expression
                 | SIZE unary_expression
                 | L_PAREN TYPE R_PAREN unary_expression
                 | exp_expression
                 ;

exp_expression : exp_expression EXP exp_expression
               | L_PAREN expression R_PAREN
               | var
               ;


/*****************
    VARIABLES
*****************/

var : TRUE
    | FALSE
    | constant
    | dataset_access
    | function_call
    | array_access
    | array_creation
    | ID
    ;

constant : NUM
         | LITERAL
         ;

dataset_access : ID PERIOD dataset_access_list

dataset_access_list : ID PERIOD dataset_access_list
                    | ID
                    ;

function_call : ID args
              ;

array_access : ID L_BRACKET expression R_BRACKET
             ;

array_literal : L_CURLY args R_CURLY
              ;

args : L_PAREN expression args_list R_PAREN
     : L_PAREN R_PAREN
     ;

arg_list : COMMA expression arg_list
         | /* empty */
         ;


