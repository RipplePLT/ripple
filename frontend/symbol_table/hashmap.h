#ifndef _HASHMAP_
#define _HASHMAP_
#include <list>
#include <string>
#include <array>
#define HASH_PRIME 31

#define TABLE_SIZE 997

using namespace std;

typedef array<list<string>*, TABLE_SIZE> table;

class HashMap{
    table t;

    public:
    HashMap();
    ~HashMap();
    string put(string word);
    bool contains(string word);
    bool remove(string word);
};

#endif
