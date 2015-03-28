%{
#include <ctype.h>
#include <stdio.h>
int yylex();
void yyerror(const char *s);
#define YYSTYPE int
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
%token SEMICOLON
%token ACCESS

%token L_PAREN
%token R_PAREN 
%token L_CURLY 
%token R_CURLY 
%token L_BRACKET 
%token R_BRACKET
%token COMMA

%%

program_declarations : program_declarations program_declaration {printf("program_declarations\n");}
					 | 
					 ;

program_declaration : import_statement {printf("program_declaration\n");}
					| final_declaration {printf("program_declaration\n");}
					| dataset_declaration {printf("program_declaration\n");}
					| function {printf("program_declaration\n");}
					;

import_statement : IMPORT LITERAL SEMICOLON {printf("import statement\n");}
				 ;

dataset_declaration : DATASET ID L_CURLY declaration_list R_CURLY {printf("dataset_declaration\n");}
					;

final_declaration : FINAL declaration {printf("final_declaration\n");}
				  ;

function : LINK declaration declaration_args L_CURLY statement_list R_CURLY {printf("function\n");}

declaration_list : declaration SEMICOLON declaration_list {printf("declaration_list\n");}
				 |
				 ;

declaration : TYPE ID {printf("program_declaration\n");}
			| ID {printf("program_declaration\n");}
			| TYPE L_BRACKET expression R_BRACKET {printf("program_declaration\n");}
			| TYPE L_BRACKET R_BRACKET {printf("program_declaration\n");}
			;

declaration_args : L_PAREN declaration declaration_arg_list R_PAREN {printf("program_declaration\n");}
				 | L_PAREN R_PAREN {printf("program_declaration\n");}
				 ;

declaration_arg_list : COMMA declaration declaration_arg_list {printf("program_declaration\n");}
					 | 
					 ;

statement_list : statement_list statement_block {printf("program_declaration\n");}
			   |
			   ;

/******************
    STATEMENTS
*******************/

statement : conditional_statement {printf("program_declaration\n");}
		  | loop_statement {printf("program_declaration\n");}
		  | link_statement {printf("program_declaration\n");}
		  | declarative_statement {printf("program_declaration\n");}
		  | jump_statement {printf("program_declaration\n");}
		  ;

conditional_statement : IF L_PAREN expression R_PAREN statement_block else_statement {printf("program_declaration\n");}
					  ;

else_statement : ELSE statement_block {printf("program_declaration\n");}
			  |
			  ;

loop_statement : WHILE L_PAREN expression R_PAREN statement_block {printf("program_declaration\n");}
               | FOR L_PAREN declarative_statement expression SEMICOLON expression R_PAREN statement_block {printf("program_declaration\n");}
               ;

link_statement : LINK L_PAREN declaration link_stream R_PAREN function_call SEMICOLON {printf("program_declaration\n");}
			   | LINK L_PAREN declaration link_stream R_PAREN SEMICOLON {printf("program_declaration\n");}
			   ;

link_stream : ARROW stream_reader {printf("program_declaration\n");}
            | ARROW expression {printf("program_declaration\n");}
            ;

stream_reader : ID L_PAREN args R_PAREN {printf("program_declaration\n");}

declarative_statement : declaration ASSIGN expression SEMICOLON {printf("program_declaration\n");}
                      | expression SEMICOLON {printf("program_declaration\n");}
                      | declaration SEMICOLON {printf("program_declaration\n");}
                      ;

declarative_statement : declaration EQ expression SEMICOLON {printf("program_declaration\n");}
                      | expression SEMICOLON {printf("program_declaration\n");}
                      | declaration SEMICOLON {printf("program_declaration\n");}
                      ;

statement_block : statement_list SEMICOLON {printf("program_declaration\n");}
                | expression SEMICOLON {printf("program_declaration\n");}
                | declaration SEMICOLON {printf("program_declaration\n");}
                ;

jump_statement : RETURN expression SEMICOLON {printf("program_declaration\n");}
               | CONTINUE SEMICOLON {printf("program_declaration\n");}
               | BREAK SEMICOLON {printf("program_declaration\n");}
               ;

/*******************
    Expressions
*******************/

expression : expression OR and_expression {printf("program_declaration\n");}
           | and_expression {printf("program_declaration\n");}
           ;

and_expression : and_expression AND eq_expression {printf("program_declaration\n");}
               | eq_expression {printf("program_declaration\n");}
               ;

eq_expression : eq_expression EQ rel_expression {printf("program_declaration\n");}
              | eq_expression NE rel_expression {printf("program_declaration\n");}
              | rel_expression {printf("program_declaration\n");}
              ;

rel_expression : rel_expression LT plus_expression {printf("program_declaration\n");}
               | rel_expression LE plus_expression {printf("program_declaration\n");}
               | rel_expression GE plus_expression {printf("program_declaration\n");}
               | rel_expression GT plus_expression {printf("program_declaration\n");}
               | plus_expression {printf("program_declaration\n");}
               ;

plus_expression : plus_expression PLUS mult_expression {printf("program_declaration\n");}
                | plus_expression MINUS mult_expression {printf("program_declaration\n");}
                | mult_expression {printf("program_declaration\n");}
                ;

mult_expression : mult_expression TIMES unary_expression {printf("program_declaration\n");}
                | mult_expression DIV unary_expression {printf("program_declaration\n");}
                | mult_expression FLDIV unary_expression {printf("program_declaration\n");}
                | mult_expression MOD unary_expression {printf("program_declaration\n");}
                | unary_expression {printf("program_declaration\n");}
                ;

unary_expression : NOT unary_expression {printf("program_declaration\n");}
                 | MINUS unary_expression {printf("program_declaration\n");}
                 | SIZE unary_expression {printf("program_declaration\n");}
                 | L_PAREN TYPE R_PAREN unary_expression {printf("program_declaration\n");}
                 | exp_expression {printf("program_declaration\n");}
                 ;

exp_expression : exp_expression EXP exp_expression {printf("program_declaration\n");}
               | L_PAREN expression R_PAREN {printf("program_declaration\n");}
               | var
               ;


/*****************
    VARIABLES
*****************/

var : TRUE {printf("program_declaration\n");}
    | FALSE {printf("program_declaration\n");}
    | constant {printf("program_declaration\n");}
    | dataset_access {printf("program_declaration\n");}
    | function_call {printf("program_declaration\n");}
    | array_access {printf("program_declaration\n");}
    | array_literal {printf("program_declaration\n");}
    | ID {printf("program_declaration\n");}
    ;

constant : NUM {printf("program_declaration\n");}
         | LITERAL {printf("program_declaration\n");}
         ;

dataset_access : ID ACCESS dataset_access_list {printf("program_declaration\n");}

dataset_access_list : ID ACCESS dataset_access_list {printf("program_declaration\n");}
                    | ID {printf("program_declaration\n");}
                    ;

function_call : ID args {printf("program_declaration\n");}
              ;

array_access : ID L_BRACKET expression R_BRACKET {printf("program_declaration\n");}
             ;

array_literal : L_CURLY args R_CURLY {printf("program_declaration\n");}
              ;

args : L_PAREN expression arg_list R_PAREN {printf("program_declaration\n");}
     | L_PAREN R_PAREN {printf("program_declaration\n");}
     ;

arg_list : COMMA expression arg_list {printf("program_declaration\n");}
         |
         ;

%%