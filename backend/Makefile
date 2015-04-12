CC=g++-4.9
CCFLAGS=-pthread -std=c++11 -Wall -Werror

main: main.o
	$(CC) main.o -o main $(CCFLAGS)

main.o: main.cpp
	$(CC) -c main.cpp $(CCFLAGS)

test: test.cpp
	$(CC) -o test test.cpp $(CCFLAGS)

clean:
	rm main *.o test
