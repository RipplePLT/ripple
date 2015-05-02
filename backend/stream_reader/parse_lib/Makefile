CC      = g++4.9
CXX     = clang++
CCFLAGS = -pthread -std=c++11
OBJS    = html_lib.o xml_lib.o
LIBS    = 

.PHONY: libs
libs: $(LIBS)

.PHONY: objects
objects: $(OBJS)

xml_lib.o: xml_lib.hpp xml_lib.cpp
	$(CXX) -c xml_lib.cpp $(CCFLAGS)

html_lib.o: html_lib.hpp html_lib.cpp
	$(CXX) -c html_lib.cpp $(CCFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJS)

.PHONY: all
all: clean objects libs
