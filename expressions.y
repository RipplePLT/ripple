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
program : program expression SEMICOLON {printf("EXPRESSION\n");}
        |
        ;

args : args COMMA expression
     | expression
     ;

expression : or_expression
           | postfix_expression ASSIGN or_expression
           ;

or_expression : and_expression
              | or_expression OR and_expression
              ;

and_expression : eq_expression
               | and_expression AND eq_expression
               ;

eq_expression : rel_expression
              | eq_expression EQ rel_expression
              | eq_expression NE rel_expression
              ;

rel_expression : add_expression
               | rel_expression GT add_expression
               | rel_expression LT add_expression
               | rel_expression GE add_expression
               | rel_expression LE add_expression
               ;

add_expression : mult_expression
               | add_expression PLUS mult_expression
               | add_expression MINUS mult_expression
               ;

mult_expression : exp_expression
                | mult_expression TIMES exp_expression
                | mult_expression DIV exp_expression
                | mult_expression FLDIV exp_expression
                | mult_expression MOD exp_expression
                ;

exp_expression : unary_expression
               | exp_expression EXP unary_expression
               ;

unary_expression : postfix_expression
                 | MINUS unary_expression
                 | SIZE unary_expression
                 | L_PAREN TYPE R_PAREN unary_expression
                 | NOT unary_expression
                 ;

postfix_expression : value
                   | postfix_expression L_BRACKET expression R_BRACKET
                   | postfix_expression L_PAREN args R_PAREN
                   | postfix_expression L_PAREN R_PAREN
                   | postfix_expression ACCESS ID
                   ;

value : ID
      | NUM
      | STRING
      | TRUE
      | FALSE
      | L_PAREN expression R_PAREN
      ;

%%
