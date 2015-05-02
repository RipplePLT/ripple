CC           = g++4.9
CXX          = clang++
CCFLAGS      = -pthread -std=c++11
OBJS         = file_lib.o html_lib.o xml_lib.o
LIBS         = libfile.a libhtml.a libxml.a
LIB_LOCATION = ../lib/libfile.a ../lib/libhtml.a ../lib/libxml.a

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
	ar rcs ../lib/libfile.a file_lib.o
	ranlib ../lib/libfile.a

libhtml.a: html_lib.o
	ar rcs ../lib/libhtml.a html_lib.o
	ranlib ../lib/libhtml.a

libxml.a: xml_lib.o
	ar rcs ../lib/libxml.a xml_lib.o
	ranlib ../lib/libxml.a

.PHONY: clean
clean:
	rm -rf $(OBJS) $(LIBS_LOCATION)

.PHONY: all
all: clean objects libs
