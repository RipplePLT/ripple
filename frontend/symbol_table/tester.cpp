#include <iostream>
#include <fstream>
#include <string>
#include "symbol_table.h"

using namespace std;

int main () {

	int line_no = 0;
	SymbolTable::SymbolTable st;

	string line;
	ifstream myfile;
	myfile.open("symbol_tester.txt");
	if(myfile.is_open()){
		while (getline(myfile,line)){
			++line_no;
			//cout << line << endl;
      		if(line.compare("{") == 0){
      			st.scope_in(line_no);
      		} else if(line.compare("}") == 0) {
      			myfile.seekg(0);
				while (getline(myfile,line)){
		  			cout << st.get(line) << endl;
				}
      		} else {
      			st.put(line);
      		}
    	}
	}
	myfile.close();
	return 0;
}
