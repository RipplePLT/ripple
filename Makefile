.PHONY: default
default: rpl

VPATH=.:frontend

CXX=g++
LEX=flex
YACC=bison

rpl: parse.o lex.o ast.o

ast.o: ast.cpp ast.h
	g++ -c frontend/ast.cpp frontend/ast.h

lex.o: lex.yy.c ast.h
	gcc -c lex.yy.c

lex.yy.c: ripple.l ripple.tab.hpp ast.h
	flex frontend/ripple.l

parse.o: ripple.tab.cpp ripple.tab.hpp ast.h
	g++ -c ripple.tab.cpp

ripple.tab.cpp: ripple.ypp ast.h
	bison -d frontend/ripple.ypp

ripple.tab.hpp: ripple.tab.cpp

.PHONY: clean
clean:
	rm -rf lex.yy.c y.tab.hpp y.tab.cpp *.o rpl

.PHONY: all
all: clean default
