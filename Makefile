.PHONY: default
default: parser

VPATH=.:frontend

CC=gcc-4.9
CXX=clang++
LEX=flex
YACC=bison
CXXFLAGS= -std=c++11 -w
LDLIBS= -L./frontend/symbol_table/
YFLAGS= -Wnone
OUT= -o $@
LFLAGS=


parser: ast.o ripple.tab.o lex.yy.o libsym.a
	$(CXX) -o parser ast.o ripple.tab.o lex.yy.o frontend/symbol_table/symbol_table.o frontend/symbol_table/hashmap.o $(LDLIBS) -lfl
	rm -f *.o *.hpp *.cpp *.c *.cc

ast.o: ast.cpp ast.h
	$(CXX) -c frontend/ast.cpp $(CXXFLAGS)

lex.yy.o: lex.yy.c ripple.tab.hpp ast.h
	$(CXX) -c lex.yy.c $(CXXFLAGS)

lex.yy.c: ripple.l ripple.tab.hpp ast.h
	$(LEX) frontend/ripple.l $(LFLAGS)

ripple.tab.o: ripple.tab.cpp ripple.tab.hpp ast.h
	$(CXX) -c ripple.tab.cpp $(CXXFLAGS)

ripple.tab.cpp ripple.tab.hpp: ripple.ypp ast.h
	$(YACC) -d frontend/ripple.ypp $(YFLAGS)

libsym.a: 
	$(MAKE) -C frontend/symbol_table
	
.PHONY: clean
clean:
	rm -f *.o *.hpp *.cpp *.c *.cc parser
	$(MAKE) -C frontend/symbol_table clean

.PHONY: all
all: clean default
