#ifndef _HASHMAP_
#define _HASHMAP_
#include <list>
#include <string>
#include <array>
#include "../../structures/enum.h"
#include "../../structures/union.h"
#define HASH_PRIME 31

#define TABLE_SIZE 997

using namespace std;

class Entry {
    public:

    string name;
    enum e_type type;
    union literal val;

    Entry(string n, string v);
    Entry(string n, long v);
    Entry(string n, double v);
    Entry(string n, bool v);
    Entry(string n, char v);
    
    bool operator==(string n);
    
    ~Entry();
};

typedef array<list<Entry *>*, TABLE_SIZE> table;

class HashMap{
    table t;

    public:
    HashMap();
    ~HashMap();
    
    bool put(string word, string v);
    bool put(string word, long v);
    bool put(string word, double v);
    bool put(string word, bool v);
    bool put(string word, char v);

    bool contains(string word);
    Entry *get(string word);
};

#endif
