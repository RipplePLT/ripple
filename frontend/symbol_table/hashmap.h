#ifndef _HASHMAP_
#define _HASHMAP_
#include <list>
#include <string>
#include <array>
#include "../../structures/enum.h"
#include "../../structures/union.h"
#define HASH_PRIME 31

#define TABLE_SIZE 97

using namespace std;

class Entry {
    public:

    string name;
    enum e_type type;
    int line_no;
    union literal val;
    enum e_symbol_type symbol_type;
    list<e_type> *args;

    Entry(string n, e_type v, int line, e_symbol_type s);

    void classify (e_symbol_type s);
    void add_args (list<e_type> *l);

    bool operator==(string n);
    
    ~Entry();
};

typedef array<list<Entry *>*, TABLE_SIZE> table;

class HashMap{
    table t;

    public:
    HashMap();
    ~HashMap();
    
    bool put(string word, e_type v, int line_no, e_symbol_type s);

    bool contains(string word);
    Entry *get(string word);
};

#endif
