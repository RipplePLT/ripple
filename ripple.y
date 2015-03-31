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
%token INTEGER
%token FLOAT_LIT 
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

%left EQ 
%left NE

%left LT 
%left LE 
%left GT 
%left GE 

%left AND
%left OR

%left PLUS 
%left MINUS 
%left TIMES 
%left DIV 
%left MOD 
%left FLDIV

%right EXP 
%right SIZE
%right NOT 

%%

/* TEMPORARY; ONLY HERE TO TEST EXPRESSIONS */
program : program expression SEMICOLON			{ printf("%d\n", $2); }
        |
        ;

args : args COMMA expression
     | expression
     ;

expression : or_expression				{ $$ = $1; }
           | value ASSIGN or_expression	
           ;

or_expression : and_expression				{ $$ = $1; }
              | or_expression OR and_expression		{ $$ = $1 || $3; }
              ;

and_expression : eq_expression				{ $$ = $1; }
               | and_expression AND eq_expression	{ $$ = $1 && $3; }
               ;

eq_expression : rel_expression				{ $$ = $1; }
              | eq_expression EQ rel_expression		{ $$ = $1 == $3; }
              | eq_expression NE rel_expression		{ $$ = $1 != $3; }
              ;

rel_expression : add_expression				{ $$ = $1; }
               | rel_expression GT add_expression	{ $$ = $1 > $3; }
               | rel_expression LT add_expression	{ $$ = $1 < $3; }
               | rel_expression GE add_expression	{ $$ = $1 >= $3; }
               | rel_expression LE add_expression	{ $$ = $1 <= $3; }
               ;

add_expression : mult_expression			{ $$ = $1; }
               | add_expression PLUS mult_expression	{ $$ = $1 + $3; }
               | add_expression MINUS mult_expression	{ $$ = $1 - $3; }
               ;

mult_expression : exp_expression			{ $$ = $1; }
                | mult_expression TIMES exp_expression	{ $$ = $1 * $3; }
                | mult_expression DIV exp_expression	{ $$ = $1 / $3; }
                | mult_expression FLDIV exp_expression	{ $$ = $1 / (double) $2; }
                | mult_expression MOD exp_expression	{ $$ = $1 % $3; }
                ;

exp_expression : unary_expression			{ $$ = $1; }
               | exp_expression EXP unary_expression
               ;

unary_expression : value				{ $$ = $1; }
                 | MINUS unary_expression		{ $$ = -$2; }
                 | SIZE unary_expression	
                 | L_PAREN TYPE R_PAREN unary_expression
                 | NOT unary_expression			{ $$ = !$2; }
                 ;

value : unit				{ $$ = $1; }
      | function_call			{ $$ = $1; }
      | array_access			{ $$ = $1; }
      | dataset_access			{ $$ = $1; }
      ;

function_call : ID L_PAREN args R_PAREN
	      | ID L_PAREN R_PAREN
	      ;

array_access : value L_BRACKET expression R_BRACKET
	     ;

dataset_access : value ACCESS ID 
	       ;

unit  : ID				 
      | INTEGER				{ $$ = $1; }
      | FLOAT_LIT			{ $$ = $1; }
      | STRING				{ $$ = $1; } 
      | TRUE				
      | FALSE				
      | L_PAREN expression R_PAREN	{ $$ = $2; }
      ;

%%
