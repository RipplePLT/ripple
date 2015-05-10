CC      = g++-4.9
CXX     = clang++
CCFLAGS = -pthread -std=c++11
OBJS    = linked_var.o link_val.o sync_queue.o expression_tree.o

.PHONY: objects
objects: $(OBJS)

linked_var.o: linked_var.cpp linked_var.h
	$(CXX) -c linked_var.cpp $(CCFLAGS)

expression_tree.o: expression_tree.cpp expression_tree.h
	$(CXX) -c expression_tree.cpp $(CCFLAGS)

link_val.o: link_val.cpp link_val.h
	$(CXX) -c link_val.cpp $(CCFLAGS)

sync_queue.o: sync_queue.cpp sync_queue.h
	$(CXX) -c sync_queue.cpp $(CCFLAGS)

.PHONY: clean-subdirs
clean-subdirs:
	cd ./parse_lib; make clean; cd ../tests; make clean;

.PHONY: clean
clean:
	rm -rf $(OBJS)

.PHONY: clean-all
clean-all: clean clean-subdirs

.PHONY: subdirs
subdirs:
	cd ./parse_lib; make all; cd ../tests; make all;

.PHONY: all
all: clean objects subdirs

.PHONY: mrproper
mrproper:
	make clean; make clean-subdirs; rm -rf lib;
