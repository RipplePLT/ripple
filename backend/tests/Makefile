CC          = g++-4.9
CXX         = clang++
CCFLAGS     = -I ../parse_lib -pthread -std=c++11
PARENT_OBJS = ../expression_tree.o ../link_val.o ../linked_var.o
CUR_OBJS    = file_parse_test.o html_parse_test.o tree_test.o \
	      vartest.o xml_parse_test.o
EXES        = file_parse_test html_parse_test tree_test vartest \
	      xml_parse_test

.PHONY: tests
tests: $(EXES)

file_parse_test: file_parse_test.o
	$(CXX) file_parse_test.o -L ../lib -lfile -lhtml -lxml -o file_parse_test

file_parse_test.o: file_parse_test.cpp file_parse_test.h
	$(CXX) -c -static file_parse_test.cpp $(CCFLAGS)

html_parse_test: html_parse_test.o
	$(CXX) html_parse_test.o -L ../lib -lhtml -lfile -lxml -o html_parse_test

html_parse_test.o: html_parse_test.cpp html_parse_test.h
	$(CXX) -c -static html_parse_test.cpp $(CCFLAGS)

tree_test: tree_test.o $(PARENT_OBJS)
	$(CXX) tree_test.o $(PARENT_OBJS) -o tree_test $(CCFLAGS) -lcurl

tree_test.o: tree_test.cpp ../streamreader/keyboard_stream_reader.h
	$(CXX) -c tree_test.cpp $(CCFLAGS)

vartest: vartest.o $(PARENT_OBJS)
	$(CXX) vartest.o $(PARENT_OBJS) -o vartest $(CCFLAGS)

vartest.o: vartest.cpp ../linked_var.o
	$(CXX) -c vartest.cpp $(CCFLAGS)

xml_parse_test: xml_parse_test.o
	$(CXX) xml_parse_test.o -L ../lib -lfile -lhtml -lxml -o xml_parse_test

xml_parse_test.o: xml_parse_test.cpp xml_parse_test.h
	$(CXX) -c -static xml_parse_test.cpp $(CCFLAGS)

.PHONY: clean
clean:
	rm -rf $(CUR_OBJS) $(EXES)

.PHONY: all
all: clean tests
