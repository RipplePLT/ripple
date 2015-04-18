%{
#include <string>
#include "frontend/ast.h"
#include "structures/enum.h"
#include "ripple.tab.hpp"

extern "C" int yywrap();
int line_no;
bool ltype;
e_type vtype;
void db(std::string m){
	//cout << m << endl;
}

%}

/* regular definitions */
delim       [ \t]
nl			\n
comment     (#.*\n)|(#\*[^(\*\#)]*\*\#)
ws          ({comment}|{delim})+
letter      [A-Za-z_]
digit       [0-9]
literal     \"([^\"]|(\\\"))*\"
id          {letter}({letter}|{digit})*
integer     {digit}+
float	    {digit}+\.{digit}*

%%

{nl}		{   line_no++;  }
{ws}        {/* don't do anything for whitespace */	}
if          {	db(yytext); ltype = false; return IF;	}
else        {	db(yytext); ltype = false; return ELSE;	}
while       {	db(yytext); ltype = false; return WHILE;	}
for         {	db(yytext); ltype = false; return FOR;	}
link        {	db(yytext); ltype = false; return LINK;	}
dataset     {	db(yytext); ltype = false; return DATASET;	}
return      {	db(yytext); ltype = false; return RETURN;	}
continue    {   db(yytext); ltype = false; return CONTINUE; }
break 		{   db(yytext); ltype = false; return BREAK; }
int         {	db(yytext); ltype = true; vtype = tINT; yylval.string = new std::string("INT"); return TYPE;	}
float       {	db(yytext); ltype = true; vtype = tFLOAT; yylval.string = new std::string("FLOAT"); return TYPE;	}
void        {	db(yytext); ltype = true; vtype = tVOID; yylval.string = new std::string("VOID"); return TYPE;	}
string      {	db(yytext); ltype = true; vtype = tSTRING; yylval.string = new std::string("STRING"); return TYPE;	}
byte        {	db(yytext); ltype = true; vtype = tBYTE; yylval.string = new std::string("BYTE"); return TYPE;	}
bool        {	db(yytext); ltype = true; vtype = tBOOL; yylval.string = new std::string("BOOL"); return TYPE;	}
true        {	db(yytext); ltype = false; yylval.boolean = true; return BOOL;}
false       {	db(yytext); ltype = false; yylval.boolean = false; return BOOL;}
not         {   db(yytext); ltype = false; return NOT; }
and         {   db(yytext); ltype = false; return AND; }
or          {   db(yytext); ltype = false; return OR; }

{id}        {	db(yytext); 
				if(ltype){
					// add the variable and type to symbol table
				} else {
					// check if id is valid
				}
				ltype = false;
				yylval.string = new std::string(yytext);
				return VAR; }

{integer}   {	db(yytext); ltype = false; yylval.integer = atoi(yytext);
		        return INTEGER;			}
{float}	    {	db(yytext); ltype = false; yylval.decimal = atof(yytext);
		        return FLOAT_LIT;		}
{literal}   {	db(yytext); ltype = false; yylval.string = new std::string(yytext);
                return LITERAL;			}

"="			{   db(yytext); ltype = false; return tASSIGN; }
"+"         {   db(yytext); ltype = false; return tPLUS;  }
"-"         {   db(yytext); ltype = false; return tMINUS; }
"*"         {   db(yytext); ltype = false; return tTIMES; } 
"/"			{	db(yytext); ltype = false; return tDIV; }
"//"		{	db(yytext); ltype = false; return tFLDIV; }
"^"			{	db(yytext); ltype = false; return tEXP;  }
"@"			{	db(yytext); ltype = false; return tSIZE; }
">"			{	db(yytext); ltype = false; return tGT;  }
"<"			{	db(yytext); ltype = false; return tLT;  }
">="		{	db(yytext); ltype = false; return tGE;	}
"<="		{	db(yytext); ltype = false; return tLE;	}
"=="		{	db(yytext); ltype = false; return tEQ; }
"!="		{	db(yytext); ltype = false; return tNE;	}
","			{	db(yytext); ltype = false; return tCOMMA; }
"("			{	db(yytext); ltype = false; return tL_PAREN; }
")"			{	db(yytext); ltype = false; return tR_PAREN; }
"["			{	db(yytext); ltype = false; return tL_BRACKET; }
"]"			{	db(yytext); ltype = false; return tR_BRACKET; }
"{"			{	db(yytext); ltype = false; return tL_CURLY; }
"}"			{	db(yytext); ltype = false; return tR_CURLY; }
";"         {   db(yytext); ltype = false; return tSEMI;  }
"\."        {  	db(yytext); ltype = false; return tACCESS; }
%%
