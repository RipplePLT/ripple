%{
#include <stdio.h>
    
#define IF 1
#define FOR 2
#define WHILE 3
#define LINK 4
#define EQ 5
#define NE 6
#define LT 7
#define LE 8
#define GT 9
#define GE 10
#define AND 11
#define OR 12
#define NOT 13
#define PLUS 14
#define MINUS 15
#define TIMES 16
#define DIV 17
#define EXP 18
#define ELSE 19
#define RELOP 20
#define ID 21
#define NUMBER 22
#define TYPE 23
#define INT 24
#define STRING 25
#define FLOAT 27
#define BYTE 28
#define BOOL 29
#define ARROW 30
#define RETURN 31
#define STRUCT 32
#define IMPORT 33
#define ARITHOP 34
#define TRUE 35
#define FALSE 36
#define ASSIGN 37
#define BOOLOP 38
#define MOD 39
#define FLDIV 40
#define ACCESS 41
#define LITERAL 42
int yylval;
%}

/* regular definitions */
delim       [ \t\n]
comment     (\/\/.*\n)|(\/\*[^(\*\/)]*\*\/)
ws          ({comment}|{delim})+
letter      [A-Za-z]
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
struct      {return STRUCT;}
return      {return RETURN;}
int         {yylval = INT; return TYPE;}
float       {yylval = FLOAT; return TYPE;}
string      {yylval = STRING; return TYPE;}
byte        {yylval = BYTE; return TYPE;}
bool        {yylval = BOOL; return TYPE;}
true        {yylval = FALSE; return BOOL;}
false       {yylval = TRUE; return BOOL;}
{id}        {return ID;}
{number}    {return NUMBER;}
{literal}   {return LITERAL;} 
"<"         {yylval = LT; return RELOP;}
"<="        {yylval = LE; return RELOP;}
"!="        {yylval = NE; return RELOP;}
"=="        {yylval = EQ; return RELOP;}
">="        {yylval = GE; return RELOP;}
">"         {yylval = GT; return RELOP;}
"&&"        {yylval = AND; return BOOLOP;}
"||"        {yylval = OR; return BOOLOP;}
"!"         {yylval = NOT; return BOOLOP;}
"+"         {yylval = PLUS; return ARITHOP;}
"-"         {yylval = MINUS; return ARITHOP;}
"*"         {yylval = TIMES; return ARITHOP;}
"/"         {yylval = DIV; return ARITHOP;}
"^"         {yylval = EXP; return ARITHOP;}
"%"         {yylval = MOD; return ARITHOP;}
"//"        {yylval = FLDIV; return ARITHOP;}
"<-"        {return ARROW;}
"="         {return ASSIGN;}
"."         {return ACCESS;}

%%

int yywrap(void) {
    return 1;
}

int main() {
    int match;
    while((match = yylex()))
        printf("%d ", match);
    printf("\n");
}
