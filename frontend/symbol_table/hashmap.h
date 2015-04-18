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

class Entry {
    string name;
    enum e_type type;
    union value val;
}
#endif
