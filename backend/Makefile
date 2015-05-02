CC      = g++-4.9
CXX     = clang++
CCFLAGS = -pthread -std=c++11
OBJS    = linked_var.o link_val.o sync_queue.o expression_tree.o

.PHONY: objects
objects: $(OBJS)

linked_var.o: linked_var.cpp linked_var.hpp
	$(CXX) -c linked_var.cpp $(CCFLAGS)

expression_tree.o: expression_tree.cpp expression_tree.hpp
	$(CXX) -c expression_tree.cpp $(CCFLAGS)

link_val.o: link_val.cpp link_val.hpp
	$(CXX) -c link_val.cpp $(CCFLAGS)

sync_queue.o: sync_queue.cpp sync_queue.hpp
	$(CXX) -c sync_queue.cpp $(CCFLAGS)

.PHONY: clean
clean:
	rm -rf $(OBJS)

.PHONY: all
all: clean objects
