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

import_statement : IMPORT LITERAL
				 ;

final_declaration : FINAL declaraion_statement
				  ;

dataset_declaration : DATASET ID L_CURLY declaration_list R_CURLY
					;

function : function_declaration L_CURLY statement_list R_CURLY
		 ;

function_declaration : LINK declaration declaration_args
					 : declaration declaration_args
					 ;

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

statement : conditional_statement 
		  | loop_statement 
		  | link_statement 
		  | declarative_statement 
		  | jump_statement
		  ;

conditional_statement : IF L_PAREN expression R_PAREN statement_block optional_else
					  ;

optional_else : ELSE statement_block 
			  |
			  ;

loop_statement : WHILE L_PAREN expression R_PAREN statement_block 
			   | FOR L_PAREN declarative_statementOPT SEMICOLON expressionOPT SEMICOLON expressionOPT R_PAREN statement_block // NEED TO FIX THIS SHIT

link_statement :  LINK L_PAREN declaration link_stream R_PAREN function_call SEMICOLON
			   : LINK L_PAREN declaration link_stream R_PAREN SEMICOLON
			   ;

link_stream : ARROW function_call 
			| ARROW expression
			;




