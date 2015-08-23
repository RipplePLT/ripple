CC  = gcc
CXX = clang++

INCLUDES =
CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall -std=c++11 $(INCLUDES)

LDFLAGS = -g
LDLIBS = -lm

default: libsym.a

libsym.a: symbol_table.o
	ar rc libsym.a symbol_table.o
	ranlib libsym.a

symbol_table.m: symbol_table.o

symbol_table.o:


.PHONY: clean
clean:
	rm -rf symbol_table.m *~ *.o *.dSYM a.out *.a

.PHONY: all
all: clean default
