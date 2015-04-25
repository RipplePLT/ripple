CC=g++-4.9
CXX=clang++
CCFLAGS=-pthread -std=c++11

main: main.o 
	$(CXX) main.o -o main $(CCFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CCFLAGS)

vartest: vartest.o
	$(CXX) vartest.o linked_var.o ../ast.o -o vartest $(CCFLAGS)

vartest.o: vartest.cpp linked_var.o
	$(CXX) -c vartest.cpp $(CCFLAGS)

linked_var.o: linked_var.cpp linked_var.hpp
	$(CXX) -c linked_var.cpp $(CCFLAGS)

clean:
	rm -rf main *.o test vartest
