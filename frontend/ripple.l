%{
#include "frontend/ast.h"
#include "ripple.tab.hpp"

#define YYSTYPE int
%}
/* regular definitions */
delim       [ \t\n]
comment     (#.*\n)|(#\*[^(\*\/)]*\*\#)
ws          ({comment}|{delim})+
letter      [A-Za-z_]
digit       [0-9]
literal     \"([^\"]|(\\\"))*\"
id          {letter}({letter}|{digit})*
integer     {digit}+
float	    {digit}+\.{digit}*

%%

{ws}        {/* don't do anything for whitespace */	}
if          {	return IF;	}
else        {	return ELSE;	}
while       {	return WHILE;	}
for         {	return FOR;	}
link        {	return LINK;	}
dataset     {	return DATASET;	}
return      {	return RETURN;	}
int         {	yylval.integer = INT; return TYPE;	}
float       {	yylval.integer = FLOAT; return TYPE;	}
void        {	yylval.integer = VOID; return TYPE;	}
string      {	yylval.integer = STRING; return TYPE;	}
byte        {	yylval.integer = BYTE; return TYPE;	}
bool        {	yylval.integer = BOOL; return TYPE;	}
true        {	yylval.boolean = true; return BOOL;}
false       {	yylval.boolean = false; return BOOL;}
{id}        {	return ID;			}
{integer}   {	yylval.integer = atoi(yytext);
		        return INTEGER;			}
{float}	    {	yylval.decimal = atof(yytext);
		        return FLOAT_LIT;		}
{literal}   {	yylval.string = yytext;
                return LITERAL;			}	 

%%

int yywrap(void) {
    return 1;
}
