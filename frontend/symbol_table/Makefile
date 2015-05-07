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

symbol_table.o: hashmap.o

hashmap.o: hashmap.h

.PHONY: clean
clean:
	rm -rf hashmap linkedlist symbol_table *~ *.o *.dSYM a.out *.a

.PHONY: cleani
cleani:
	rm -rf hashmap linkedlist symbol_table *~ *.o *.dSYM a.out

.PHONY: all
all: clean default
