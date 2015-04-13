%{
#include <string>
#include "frontend/ast.h"
#include "ripple.tab.hpp"
extern "C" int yywrap();
int line_no;

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
if          {	db(yytext);return IF;	}
else        {	db(yytext);return ELSE;	}
while       {	db(yytext);return WHILE;	}
for         {	db(yytext);return FOR;	}
link        {	db(yytext);return LINK;	}
dataset     {	db(yytext);return DATASET;	}
return      {	db(yytext);return RETURN;	}
continue    {   db(yytext);return CONTINUE; }
break 		{   db(yytext);return BREAK; }
int         {	db(yytext);yylval.string = new std::string("INT"); return TYPE;	}
float       {	db(yytext);yylval.string = new std::string("FLOAT"); return TYPE;	}
void        {	db(yytext);yylval.string = new std::string("VOID"); return TYPE;	}
string      {	db(yytext);yylval.string = new std::string("STRING"); return TYPE;	}
byte        {	db(yytext);yylval.string = new std::string("BYTE"); return TYPE;	}
bool        {	db(yytext);yylval.string = new std::string("BOOL"); return TYPE;	}
true        {	db(yytext);yylval.boolean = true; return BOOL;}
false       {	db(yytext);yylval.boolean = false; return BOOL;}
not         {   db(yytext);return NOT; }
and         {   db(yytext);return AND; }
or          {   db(yytext);return OR; }
{id}        {	db(yytext);yylval.string = new std::string(yytext); return VAR; }
{integer}   {	db(yytext);yylval.integer = atoi(yytext);
		        return INTEGER;			}
{float}	    {	db(yytext);yylval.decimal = atof(yytext);
		        return FLOAT_LIT;		}
{literal}   {	db(yytext);yylval.string = new std::string(yytext);
                return LITERAL;			}
"="			{   db(yytext);return tASSIGN; }
"+"         {   db(yytext);return tPLUS;  }
"-"         {   db(yytext);return tMINUS; }
"*"         {   db(yytext);return tTIMES; } 
"/"			{	db(yytext);return tDIV; }
"//"		{	db(yytext);return tFLDIV; }
"^"			{	db(yytext);return tEXP;  }
"@"			{	db(yytext);return tSIZE; }
">"			{	db(yytext);return tGT;  }
"<"			{	db(yytext);return tLT;  }
">="		{	db(yytext);return tGE;	}
"<="		{	db(yytext);return tLE;	}
"=="		{	db(yytext);return tEQ; }
"!="		{	db(yytext);return tNE;	}
","			{	db(yytext);return tCOMMA; }
"("			{	db(yytext);return tL_PAREN; }
")"			{	db(yytext);return tR_PAREN; }
"["			{	db(yytext);return tL_BRACKET; }
"]"			{	db(yytext);return tR_BRACKET; }
"{"			{	db(yytext);return tL_CURLY; }
"}"			{	db(yytext);return tR_CURLY; }
";"         {   db(yytext);return tSEMI;  }
"\."        {  	db(yytext);return tACCESS; }
%%
