CC=g++-4.9
CXX=clang++
CCFLAGS=-pthread -std=c++11 -Wall -Werror

main: main.o 
	$(CXX) main.o -o main $(CCFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CCFLAGS)

vartest: vartest.o
	$(CXX) vartest.o linkedvar.o variable_tree.o -o vartest $(CCFLAGS)

vartest.o: vartest.cpp linkedvar.o variable_tree.o
	$(CXX) -c vartest.cpp $(CCFLAGS)

linkedvar.o: linkedvar.cpp linkedvar.hpp
	$(CXX) -c linkedvar.cpp $(CCFLAGS)

variable_tree.o: variable_tree.cpp variable_tree.hpp
	$(CXX) -c variable_tree.cpp $(CCFLAGS)

clean:
	rm -rf main *.o test vartest
