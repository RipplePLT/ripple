%{
#include <string>
#include "frontend/ast.h"
#include "structures/enum.h"
#include "ripple.tab.hpp"
#include "frontend/symbol_table/symbol_table.h"

void install_id();

extern "C" int yywrap();

int line_no = 1;
bool error = false;
string filename_cpp;
string filename;
string cpp_code;

bool saw_type;
bool saw_id;
string last_id;
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
{ws}        {   /* don't do anything for whitespace */	}
if          {	db(yytext); saw_id = false; return IF;	}
else        {	db(yytext); saw_id = false; return ELSE;	}
while       {	db(yytext); saw_id = false; return WHILE;	}
for         {	db(yytext); saw_id = false; return FOR;	}
link        {	db(yytext); saw_id = false; return LINK;	}
dataset     {	db(yytext); saw_id = false; return DATASET;	}
return      {	db(yytext); saw_id = false; return RETURN;	}
continue    {   db(yytext); saw_id = false; return CONTINUE; }
break 		{   db(yytext); saw_id = false; return BREAK; }
int         {	db(yytext); saw_id = false; last_type = tINT; yylval.string = new std::string("INT"); return TYPE;	}
float       {	db(yytext); saw_id = false; last_type = tFLOAT; yylval.string = new std::string("FLOAT"); return TYPE;	}
void        {	db(yytext); saw_id = false; last_type = tVOID; yylval.string = new std::string("VOID"); return TYPE;	}
string      {	db(yytext); saw_id = false; last_type = tSTRING; yylval.string = new std::string("STRING"); return TYPE;	}
byte        {	db(yytext); saw_id = false; last_type = tBYTE; yylval.string = new std::string("BYTE"); return TYPE;	}
bool        {	db(yytext); saw_id = false; last_type = tBOOL; yylval.string = new std::string("BOOL"); return TYPE;	}
true        {	db(yytext); saw_id = false; yylval.boolean = true; return TRUE;}
false       {	db(yytext); saw_id = false; yylval.boolean = false; return FALSE;}
not         {   db(yytext); saw_id = false; return NOT; }
and         {   db(yytext); saw_id = false; return AND; }
or          {   db(yytext); saw_id = false; return OR; }

{id}        {	db(yytext); 
				yylval.string = new std::string(yytext);
				saw_id = true;
                last_id = std::string(yytext);
                return ID;
			}

{integer}   {	db(yytext); saw_id = false; yylval.integer = atoi(yytext);
		        return INTEGER;	}
{float}	    {	db(yytext); saw_id = false; yylval.decimal = atof(yytext);
		        return FLOAT_LIT; }
{literal}   {	db(yytext); saw_id = false; yylval.string = new string(yytext);
                return STRING_LITERAL; }

"="			{   db(yytext); saw_id = false; return tASSIGN; }
"+"         {   db(yytext); saw_id = false; return tPLUS;  }
"-"         {   db(yytext); saw_id = false; return tMINUS; }
"*"         {   db(yytext); saw_id = false; return tTIMES; } 
"/"			{	db(yytext); saw_id = false; return tDIV; }
"//"		{	db(yytext); saw_id = false; return tFLDIV; }
"%"         {   db(yytext); saw_id = false; return tMOD; }
"^"			{	db(yytext); saw_id = false; return tEXP;  }
"@"			{	db(yytext); saw_id = false; return tSIZE; }
">"			{	db(yytext); saw_id = false; return tGT;  }
"<"			{	db(yytext); saw_id = false; return tLT;  }
">="		{	db(yytext); saw_id = false; return tGE;	}
"<="		{	db(yytext); saw_id = false; return tLE;	}
"=="		{	db(yytext); saw_id = false; return tEQ; }
"!="		{	db(yytext); saw_id = false; return tNE;	}
","			{	db(yytext); saw_id = false; return tCOMMA; }
"("			{	db(yytext); saw_id = false; return tL_PAREN; }
")"			{	db(yytext); saw_id = false; return tR_PAREN; }
"["			{	db(yytext); saw_id = false; return tL_BRACKET; }
"]"			{	db(yytext); saw_id = false; return tR_BRACKET; }
"{"			{	db(yytext); if(saw_id) sym_table.new_dataset(line_no, last_id); else sym_table.scope_in(line_no); saw_id = false; return tL_CURLY; }
"}"			{	db(yytext); sym_table.scope_out(line_no); return tR_CURLY; }
";"         {   db(yytext); saw_id = false; return tSEMI;  }
"\."        {  	db(yytext); saw_id = false; return tACCESS; }
%%


int main(int argc, char **argv) {

	if(argc < 2){
		cout << "usage ./rpl <input_file> [output_file]" << endl;
		exit(1);
	} else if (argc < 3){
		filename = "output";
        filename_cpp = "output.cpp";
	}
	else {
		filename = argv[2];
        filename_cpp = filename + ".cpp";
	}

    yyin = fopen(argv[1], "r");
    yyout = fopen(filename_cpp.c_str(), "w");
    yyparse();
    
    if(error){
    	cout << COMPILE_ERR << endl;
    	return 1;
    }
    write_to_file(filename_cpp, cpp_code);
    string compile_cpp = "clang++ " + filename_cpp + " -o " + filename;
    system(compile_cpp.c_str());
   
#ifndef DEBUG
    remove(filename_cpp.c_str());
#endif
    return 0;
}
