
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

