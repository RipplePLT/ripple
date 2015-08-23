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

RIPPLE2OBJS = \
literal_node.o \
value_node.o \
unary_expression_node.o \
binary_expression_node.o \


OBJS=ast.o ${RIPPLE2OBJS} ripple2.tab.o lex.yy.o frontend/symbol_table/symbol_table.o \
     frontend/symbol_table/hashmap.o frontend/symbol_table2/symbol_table.o debug_tools.o
BACKEND_OBJS=backend/linked_var.o backend/expression_tree.o backend/link_val.o

rpl: ast.o rpl2 ripple2.tab.o lex.yy.o debug_tools.o libsym.a libbackend.a libfile.a
	$(CXX) -o rpl $(OBJS) $(LDLIBS) -lfl -lfile -lxml -lhtml 
	rm -f *.o *.hpp *.cpp *.c *.cc

ast.o: ast.cpp ast.h
	$(CXX) -c frontend/ast.cpp $(CXXFLAGS)

debug_tools.o: debug_tools.cpp debug_tools.h
	$(CXX) -c misc/debug_tools.cpp $(CXXFLAGS)

lex.yy.o: lex.yy.c ripple2.tab.h ast.h debug_tools.h
	$(CXX) -c lex.yy.c $(CXXFLAGS)

lex.yy.c: ripple.l ripple2.tab.h ast.h
	$(LEX) frontend/ripple.l $(LFLAGS)

ripple2.tab.o: ripple2.tab.cpp ripple2.tab.h ast.h
	$(CXX) -c ripple2.tab.cpp $(CXXFLAGS)

ripple2.tab.cpp ripple2.tab.h: ripple2.ypp ast.h
	$(YACC) -d frontend/ripple2.ypp $(YFLAGS)

libsym.a: 
	$(MAKE) -C frontend/symbol_table
	$(MAKE) -C frontend/symbol_table2	

libbackend.a: backend/linked_var.o backend/expression_tree.o backend/link_val.o
	ar rcs libbackend.a $(BACKEND_OBJS)
	ranlib libbackend.a

libfile.a:
	$(MAKE) -C backend all

#RIPPLE 2.0 Objects
rpl2: literal_node.o value_node.o unary_expression_node.o binary_expression_node.o

literal_node.o: ast_nodes/literal_node.cpp ast_nodes/literal_node.h
	$(CXX) -c frontend/ast_nodes/literal_node.cpp $(CXXFLAGS)

value_node.o: ast_nodes/value_node.cpp ast_nodes/value_node.h
	$(CXX) -c frontend/ast_nodes/value_node.cpp $(CXXFLAGS)

unary_expression_node.o: ast_nodes/unary_expression_node.cpp ast_nodes/unary_expression_node.h
	$(CXX) -c frontend/ast_nodes/unary_expression_node.cpp $(CXXFLAGS)

binary_expression_node.o: ast_nodes/binary_expression_node.cpp ast_nodes/binary_expression_node.h
	$(CXX) -c frontend/ast_nodes/binary_expression_node.cpp $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f *.o *.hpp *.cpp *.c *.cc *.a rpl output
	$(MAKE) -C frontend/symbol_table clean
	$(MAKE) -C frontend/symbol_table2 clean
	$(MAKE) -C backend mrproper

.PHONY: all
all: clean default
