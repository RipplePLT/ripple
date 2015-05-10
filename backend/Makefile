CC      = g++-4.9
CXX     = clang++
CCFLAGS = -pthread -std=c++11
OBJS    = linked_var.o link_val.o expression_tree.o

.PHONY: objects
objects: $(OBJS)

linked_var.o: linked_var.cpp linked_var.h
	$(CXX) -c linked_var.cpp $(CCFLAGS)

expression_tree.o: expression_tree.cpp expression_tree.h
	$(CXX) -c expression_tree.cpp $(CCFLAGS)

link_val.o: link_val.cpp link_val.h
	$(CXX) -c link_val.cpp $(CCFLAGS)

.PHONY: clean-subdirs
clean-subdirs:
	$(MAKE) -C parse_lib clean
	$(MAKE) -C tests clean

.PHONY: clean
clean:
	rm -rf $(OBJS) streamreader/*.gch

.PHONY: clean-all
clean-all: clean clean-subdirs

.PHONY: subdirs
subdirs:
	$(MAKE) -C parse_lib all
	$(MAKE) -C tests all

.PHONY: all
all: clean objects subdirs

.PHONY: mrproper
mrproper:
	$(MAKE) clean
	$(MAKE) clean-subdirs
	rm -rf lib
