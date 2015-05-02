CC          = g++-4.9
CXX         = clang++
CCFLAGS     = -pthread -std=c++11
PARENT_OBJS = ../expression_tree.o ../link_val.o ../linked_var.o
CUR_OBJS    = tree_test.o sync_test.o vartest.o
EXES        = vartest sync_test tree_test

.PHONY: tests
tests: $(EXES)

sync_test: sync_test.o ../sync_queue.o
	$(CXX) sync_test.o ../sync_queue.o -o sync_test $(CCFLAGS)

sync_test.o: sync_test.cpp sync_test.hpp
	$(CXX) -c sync_test.cpp $(CCFLAGS)

tree_test: tree_test.o $(PARENT_OBJS)
	$(CXX) tree_test.o $(PARENT_OBJS) -o tree_test

tree_test.o: tree_test.cpp
	$(CXX) -c tree_test.cpp $(CCFLAGS)


vartest: vartest.o $(PARENT_OBJS)
	$(CXX) vartest.o $(PARENT_OBJS) -o vartest $(CCFLAGS)

vartest.o: vartest.cpp ../linked_var.o
	$(CXX) -c vartest.cpp $(CCFLAGS)

.PHONY: clean
clean:
	rm -rf $(CUR_OBJS) $(EXES)

.PHONY: all
all: clean tests
