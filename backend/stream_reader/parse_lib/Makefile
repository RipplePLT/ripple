CC      = g++4.9
CXX     = clang++
CCFLAGS = -pthread -std=c++11
OBJS    = file_lib.o html_lib.o xml_lib.o
LIBS    = libfile.a libhtml.a libxml.a

.PHONY: default
default: objects libs

.PHONY: objects
objects: $(OBJS)

file_lib.o: file_lib.hpp file_lib.cpp
	$(CXX) -c file_lib.cpp $(CCFLAGS)

html_lib.o: html_lib.hpp html_lib.cpp
	$(CXX) -c html_lib.cpp $(CCFLAGS)

xml_lib.o: xml_lib.hpp xml_lib.cpp
	$(CXX) -c xml_lib.cpp $(CCFLAGS)

.PHONY: libs
libs: $(LIBS)

libfile.a: file_lib.o
	ar rcs libfile.a libfile.a

libhtml.a: html_lib.o
	ar rcs libhtml.a html_lib.o

libxml.a: xml_lib.o
	ar rcs libxml.a xml_lib.o

.PHONY: clean
clean:
	rm -rf $(OBJS) $(LIBS)

.PHONY: all
all: clean objects libs
