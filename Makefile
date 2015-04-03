.PHONY: default
default: rpl

VPATH=.:frontend

CC=gcc-4.9
CXX=clang++
LEX=flex
YACC=bison
CXXFLAGS= -std=c++11 -w
YFLAGS= -Wnone
OUT= -o $@
LFLAGS=

rpl: ast.o ripple.tab.o lex.yy.o
	$(CXX) -o rpl ast.o ripple.tab.o lex.yy.o -lfl
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


.PHONY: clean
clean:
	rm -f *.o *.hpp *.cpp *.c *.cc rpl

.PHONY: all
all: clean default
