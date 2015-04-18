CC=g++-4.9
CCFLAGS=-pthread -std=c++11 -Wall -Werror

main: main.o 
	$(CC) main.o -o main $(CCFLAGS)

main.o: main.cpp variable.hpp variable.cpp
	$(CC) -c main.cpp $(CCFLAGS)

vartest: vartest.o
	$(CC) vartest.o -o vartest $(CCFLAGS)

vartest.o: vartest.cpp ../frontend/ast.h
	$(CC) -c vartest.cpp $(CCFLAGS)

clean:
	rm -rf main *.o test
