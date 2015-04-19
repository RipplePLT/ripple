CC=g++-4.9
CXX=clang++
CCFLAGS=-pthread -std=c++11 -Wall -Werror
CXXFLAGS= -std=c++11 -w

main: main.o 
	$(CXX) main.o -o main $(CXXFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CXXFLAGS)

vartest: vartest.o ../ast.o
	$(CXX) vartest.o ../ast.o -o vartest $(CXXFLAGS)

vartest.o: vartest.cpp ../frontend/ast.h linkedvar.o
	$(CXX) -c vartest.cpp $(CXXFLAGS)

linkedvar.o: linkedvar.cpp linkedvar.hpp
	$(CXX) -c linkedvar.cpp $(CXXFLAGS)

clean:
	rm -rf main *.o test vartest
