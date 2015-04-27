CC = g++-4.9
CXX = clang++
CCFLAGS = -pthread -std=c++11

.PHONY: tests
tests: vartest sync_test

main: main.o 
	$(CXX) main.o -o main $(CCFLAGS)

main.o: main.cpp
	$(CXX) -c main.cpp $(CCFLAGS)

vartest: vartest.o expression_tree.o
	$(CXX) vartest.o linked_var.o expression_tree.o -o vartest $(CCFLAGS)

vartest.o: vartest.cpp linked_var.o
	$(CXX) -c vartest.cpp $(CCFLAGS)

linked_var.o: linked_var.cpp linked_var.hpp
	$(CXX) -c linked_var.cpp $(CCFLAGS)

expression_tree.o: expression_tree.cpp expression_tree.hpp
	$(CXX) -c expression_tree.cpp $(CCFLAGS)

sync_test: sync_test.o sync_queue.o
	$(CXX) sync_test.o sync_queue.o -o sync_test $(CCFLAGS)

sync_test.o: sync_test.cpp sync_test.hpp
	$(CXX) -c sync_test.cpp $(CCFLAGS)

sync_queue.o: sync_queue.cpp sync_queue.hpp
	$(CXX) -c sync_queue.cpp $(CCFLAGS)

.PHONY: clean
clean:
	rm -rf main *.o test vartest sync_test

.PHONY: all
all: clean sync_test vartest main test
