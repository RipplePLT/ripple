%{
#include <stdio.h>
int yylval;
%}
/***************
    KEYWORDS 
***************/
%token IF
%token ELSE
%token FOR
%token WHILE
%token LINK
%token IMPORT
%token FINAL
%token RETURN
%token CONTINUE
%token BREAK

/***************
      TYPES 
***************/
%token TYPE
%token BOOL
%token BYTE
%token INT
%token FLOAT
%token STRING 
%token DATASET
%token VOID

/***************
       OP
***************/
%token EQ 
%token NE
%token LT 
%token LE 
%token GT 
%token GE 

%token PLUS 
%token MINUS 
%token TIMES 
%token DIV 
%token MOD 
%token FLDIV 
%token EXP 
%token SIZE

%token AND 
%token OR 
%token NOT 

/***************
    VARIABLES 
***************/
%token ID
%token NUM 
%token LITERAL 
%token TRUE
%token FALSE

/***************
    LITERALS
***************/
%token ARROW
%token ASSIGN
%token SEMICOL
%token ACCESS

%token L_PAREN
%token R_PAREN 
%token L_CURLY 
%token R_CURLY 
%token L_BRACKET 
%token R_BRACKET
%token COMMA

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

final_declaration : FINAL declaration
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

stream_reader : ID L_PAREN args R_PAREN

declarative_statement : declaration ASSIGN expression SEMICOLON
                      | expression SEMICOLON
                      | declaration SEMICOLON
                      ;

declarative_statement : declaration EQ expression SEMICOLON
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
    | array_literal 
    | ID
    ;

constant : NUM
         | LITERAL
         ;

dataset_access : ID ACCESS dataset_access_list

dataset_access_list : ID ACCESS dataset_access_list
                    | ID
                    ;

function_call : ID args
              ;

array_access : ID L_BRACKET expression R_BRACKET
             ;

array_literal : L_CURLY args R_CURLY
              ;

args : L_PAREN expression arg_list R_PAREN
     | L_PAREN R_PAREN
     ;

arg_list : COMMA expression arg_list
         | /* empty */
         ;

%%

