%{
#include <string>
#include "frontend/ast.h"
#include "ripple.tab.hpp"
extern "C" int yywrap();
int line_no;
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
if          {	return IF;	}
else        {	return ELSE;	}
while       {	return WHILE;	}
for         {	return FOR;	}
link        {	return LINK;	}
dataset     {	return DATASET;	}
return      {	return RETURN;	}
int         {	yylval.string = new std::string("INT"); return TYPE;	}
float       {	yylval.string = new std::string("FLOAT"); return TYPE;	}
void        {	yylval.string = new std::string("VOID"); return TYPE;	}
string      {	yylval.string = new std::string("STRING"); return TYPE;	}
byte        {	yylval.string = new std::string("BYTE"); return TYPE;	}
bool        {	yylval.string = new std::string("BOOL"); return TYPE;	}
true        {	yylval.boolean = true; return BOOL;}
false       {	yylval.boolean = false; return BOOL;}
not         {   return NOT; }
and         {   return AND; }
or          {   return OR; }
{id}        {	return ID; 		}
{integer}   {	yylval.integer = atoi(yytext);
		        return INTEGER;			}
{float}	    {	yylval.decimal = atof(yytext);
		        return FLOAT_LIT;		}
{literal}   {	yylval.string = new std::string(yytext);
                return LITERAL;			}
"="			{   return tASSIGN; }
"+"         {   return tPLUS;  }
"-"         {   return tMINUS; }
"*"         {   return tTIMES; } 
"/"			{	return tDIV; }
"//"		{	return tFLDIV; }
"^"			{	return tEXP;  }
"@"			{	return tSIZE; }
">"			{	return tGT;  }
"<"			{	return tLT;  }
">="		{	return tGE;	}
"<="		{	return tLE;	}
"=="		{	return tEQ; }
"!="		{	return tNE;	}
","			{	return tCOMMA; }
"("			{	return tL_PAREN; }
")"			{	return tR_PAREN; }
"["			{	return tL_BRACKET; }
"]"			{	return tR_BRACKET; }
"{"			{	return tL_CURLY; }
"}"			{	return tR_CURLY; }
";"         {   return tSEMI;  }
"\."        {  return tACCESS; }
%%
