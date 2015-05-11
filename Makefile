.PHONY: default
default: rpl

VPATH=.:frontend:misc

ydebug: MODE=-DDEBUG
ydebug: rpl

ldebug: MODE=-DLDEBUG
ldebug: rpl

MODE=
CC=gcc-4.9
CXX=clang++
LEX=flex
YACC=bison
CXXFLAGS= -std=c++11 -w $(INCLUDES) $(MODE)
LDLIBS= -L./frontend/symbol_table/ -L./backend/lib/
INCLUDES= -I./link_files/ -I./backend/streamreader/
YFLAGS= -Wnone 
LFLAGS= 
MISCFLAGS= 
OBJS=ast.o ripple.tab.o lex.yy.o frontend/symbol_table/symbol_table.o \
     frontend/symbol_table/hashmap.o debug_tools.o
BACKEND_OBJS=backend/linked_var.o backend/expression_tree.o backend/link_val.o

rpl: ast.o ripple.tab.o lex.yy.o debug_tools.o libsym.a libbackend.a libfile.a 
	$(CXX) -o rpl $(OBJS) $(LDLIBS) -lfl -lfile -lxml -lhtml
	rm -f *.o *.hpp *.cpp *.c *.cc

ast.o: ast.cpp ast.h
	$(CXX) -c frontend/ast.cpp $(CXXFLAGS)

debug_tools.o: debug_tools.cpp debug_tools.h
	$(CXX) -c misc/debug_tools.cpp $(CXXFLAGS)

lex.yy.o: lex.yy.c ripple.tab.h ast.h debug_tools.h
	$(CXX) -c lex.yy.c $(CXXFLAGS)

lex.yy.c: ripple.l ripple.tab.h ast.h
	$(LEX) frontend/ripple.l $(LFLAGS)

ripple.tab.o: ripple.tab.cpp ripple.tab.h ast.h
	$(CXX) -c ripple.tab.cpp $(CXXFLAGS)

ripple.tab.cpp ripple.tab.h: ripple.ypp ast.h
	$(YACC) -d frontend/ripple.ypp $(YFLAGS)

libsym.a: 
	$(MAKE) -C frontend/symbol_table

libbackend.a: backend/linked_var.o backend/expression_tree.o backend/link_val.o
	ar rcs libbackend.a $(BACKEND_OBJS)
	ranlib libbackend.a

libfile.a:
	$(MAKE) -C backend all

.PHONY: clean
clean:
	rm -f *.o *.hpp *.cpp *.c *.cc *.a rpl output
	$(MAKE) -C frontend/symbol_table clean
	$(MAKE) -C backend mrproper

.PHONY: all
all: clean default
