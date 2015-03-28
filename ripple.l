%{
#include <stdio.h>
#include "y.tab.h"
%}

/* regular definitions */
delim       [ \t\n]
comment     (#.*\n)|(#\*[^(\*\/)]*\*\#)
ws          ({comment}|{delim})+
letter      [A-Za-z_]
digit       [0-9]
literal     \"([^\"]|(\\\"))*\"
id          {letter}({letter}|{digit})*
number      {digit}+(\.{digit}+)?

%%

{ws}        {/* don't do anything for whitespace */}
if          {return IF;}
else        {return ELSE;}
while       {return WHILE;}
for         {return FOR;}
link        {return LINK;}
dataset     {return DATASET;}
return      {return RETURN;}
int         {yylval = INT; return TYPE;}
float       {yylval = FLOAT; return TYPE;}
void        {yylval = VOID; return TYPE;}
string      {yylval = STRING; return TYPE;}
byte        {yylval = BYTE; return TYPE;}
bool        {yylval = BOOL; return TYPE;}
true        {yylval = FALSE; return BOOL;}
false       {yylval = TRUE; return BOOL;}
{id}        {return ID;}
{number}    {return NUM;}
{literal}   {return LITERAL;} 
"<"         {yylval = LT; return LT;}
"<="        {yylval = LE; return LE;}
"!="        {yylval = NE; return NE;}
"=="        {yylval = EQ; return EQ;}
">="        {yylval = GE; return GE;}
">"         {yylval = GT; return GT;}
"&&"        {yylval = AND; return AND;}
"||"        {yylval = OR; return OR;}
"+"         {yylval = PLUS; return PLUS;}
"-"         {yylval = MINUS; return MINUS;}
"*"         {yylval = TIMES; return TIMES;}
"/"         {yylval = DIV; return DIV;}
"^"         {yylval = EXP; return EXP;}
"%"         {yylval = MOD; return MOD;}
"//"        {yylval = FLDIV; return FLDIV;}
"<-"        {return ARROW;}
"="         {return ASSIGN;}
"."         {return ACCESS;}
";"			{return SEMICOL;}
"("			{return L_CURLY;}
")"			{return R_CURLY;}
"["			{return L_BRACKET;}
"]"			{return R_BRACKET;}
"{"			{return L_CURLY;}
"}"			{return R_CURLY;}
","         {return COMMA;}

%%

