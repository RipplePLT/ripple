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


int yylval;
%}

/* regular definitions */
delim       [ \t\n]
comment     (\/\/.*\n)|(\/\*[^(\*\/)]*\*\/)
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
"!"         {yylval = NOT; return NOT;}
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
