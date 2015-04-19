%{
#include <string>
#include "frontend/ast.h"
#include "structures/enum.h"
#include "ripple.tab.hpp"
#include "frontend/symbol_table/symbol_table.h"

extern "C" int yywrap();

int line_no = 1;
bool error = false;
string filename;

bool saw_type;
e_type last_type;
void db(std::string m){
	//cout << m << endl;
}

SymbolTable sym_table;

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
if          {	db(yytext); saw_type = false; return IF;	}
else        {	db(yytext); saw_type = false; return ELSE;	}
while       {	db(yytext); saw_type = false; return WHILE;	}
for         {	db(yytext); saw_type = false; return FOR;	}
link        {	db(yytext); saw_type = false; return LINK;	}
dataset     {	db(yytext); saw_type = false; return DATASET;	}
return      {	db(yytext); saw_type = false; return RETURN;	}
continue    {   db(yytext); saw_type = false; return CONTINUE; }
break 		{   db(yytext); saw_type = false; return BREAK; }
int         {	db(yytext); saw_type = true; last_type = tINT; yylval.string = new std::string("INT"); return TYPE;	}
float       {	db(yytext); saw_type = true; last_type = tFLOAT; yylval.string = new std::string("FLOAT"); return TYPE;	}
void        {	db(yytext); saw_type = true; last_type = tVOID; yylval.string = new std::string("VOID"); return TYPE;	}
string      {	db(yytext); saw_type = true; last_type = tSTRING; yylval.string = new std::string("STRING"); return TYPE;	}
byte        {	db(yytext); saw_type = true; last_type = tBYTE; yylval.string = new std::string("BYTE"); return TYPE;	}
bool        {	db(yytext); saw_type = true; last_type = tBOOL; yylval.string = new std::string("BOOL"); return TYPE;	}
true        {	db(yytext); saw_type = false; yylval.boolean = true; return TRUE;}
false       {	db(yytext); saw_type = false; yylval.boolean = false; return FALSE;}
not         {   db(yytext); saw_type = false; return NOT; }
and         {   db(yytext); saw_type = false; return AND; }
or          {   db(yytext); saw_type = false; return OR; }

{id}        {	db(yytext); 

				if(saw_type){
					if(sym_table.contains_in_scope(yytext)) {
					    error = true;
					    Entry *entry = sym_table.get(yytext);
					    cout << "Redefinition of variable " << yytext << " previously defined on line " << entry->line_no << endl;
					} else if (sym_table.contains(yytext)) {
						// possible redeclaration
					} else {
						if(!sym_table.put(yytext, last_type, line_no))
							exit(1);
					}
				} else {
					// check if id is valid
					if(!sym_table.contains(yytext))
						cout << "Use of undeclared identifier " << yytext << " on line " << line_no << endl;
				}
				saw_type = false;
				yylval.string = new std::string(yytext);
				return VAR;
			}

{integer}   {	db(yytext); saw_type = false; yylval.integer = atoi(yytext);
		        return INTEGER;	}
{float}	    {	db(yytext); saw_type = false; yylval.decimal = atof(yytext);
		        return FLOAT_LIT; }
{literal}   {	db(yytext); saw_type = false; yylval.string = new string(yytext);
                return STRING_LITERAL; }

"="			{   db(yytext); saw_type = false; return tASSIGN; }
"+"         {   db(yytext); saw_type = false; return tPLUS;  }
"-"         {   db(yytext); saw_type = false; return tMINUS; }
"*"         {   db(yytext); saw_type = false; return tTIMES; } 
"/"			{	db(yytext); saw_type = false; return tDIV; }
"//"		{	db(yytext); saw_type = false; return tFLDIV; }
"^"			{	db(yytext); saw_type = false; return tEXP;  }
"@"			{	db(yytext); saw_type = false; return tSIZE; }
">"			{	db(yytext); saw_type = false; return tGT;  }
"<"			{	db(yytext); saw_type = false; return tLT;  }
">="		{	db(yytext); saw_type = false; return tGE;	}
"<="		{	db(yytext); saw_type = false; return tLE;	}
"=="		{	db(yytext); saw_type = false; return tEQ; }
"!="		{	db(yytext); saw_type = false; return tNE;	}
","			{	db(yytext); saw_type = false; return tCOMMA; }
"("			{	db(yytext); saw_type = false; return tL_PAREN; }
")"			{	db(yytext); saw_type = false; return tR_PAREN; }
"["			{	db(yytext); saw_type = false; return tL_BRACKET; }
"]"			{	db(yytext); saw_type = false; return tR_BRACKET; }
"{"			{	db(yytext); sym_table.scope_in(line_no); saw_type = false; return tL_CURLY; }
"}"			{	db(yytext); sym_table.scope_out(line_no); saw_type = false; return tR_CURLY; }
";"         {   db(yytext); saw_type = false; return tSEMI;  }
"\."        {  	db(yytext); saw_type = false; return tACCESS; }
%%

int main(int argc, char **argv) {

	if(argc < 2){
		cout << "usage ./rpl <input_file> [output_file]" << endl;
		exit(1);
	} else if (argc < 3){
		filename = "ripple.cpp";
	}
	else {
		filename = argv[2];
	}

    sym_table.scope_in(0);
    sym_table.put("print", tVOID, 0);
    yyin = fopen(argv[1], "r");
    yyparse();
    return 0;
}
