CC=g++-4.9
CXX=clang++
CCFLAGS=-pthread -std=c++11 -Wall -Werror

main: main.o 
	$(CXX) main.o -o main $(CCFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CCFLAGS)

vartest: vartest.o
	$(CXX) vartest.o ../ast.o linkedvar.o ../frontend/symbol_table/hashmap.o -o vartest $(CCFLAGS)

vartest.o: vartest.cpp ../frontend/ast.h linkedvar.o
	$(CXX) -c vartest.cpp $(CCFLAGS)

linkedvar.o: linkedvar.cpp linkedvar.hpp
	$(CXX) -c linkedvar.cpp $(CCFLAGS)

clean:
	rm -rf main *.o test vartest
