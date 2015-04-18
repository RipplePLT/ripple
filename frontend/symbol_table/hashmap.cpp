#include <cmath>
#include "hashmap.h"

using namespace std;

bool list_contains(list<Entry *> l, string word) { 
    for (auto element = l.begin(); element != l.end(); ++element) {
        if ((*element)->name.compare(word) == 0 ) {
            return true;
        }
    }
    return false;
}

int hashCode(const string word) {

    int h = 0;

    if (word.length() > 0) {
        int i;
        for (i = 0; i < word.length(); i++) {
            h = HASH_PRIME * h + word[i];
        }
    }

    return (int) std::abs((float) h);
}


int isPrime(int num){

    if(num < 4)
        return 0;

    int max = (int) pow(num, 0.5) + 1;
    int i;
    for( i = 2; i < max ; ++i )
        if(num % i == 0) 
            return 0;
    return 1;
}


HashMap::HashMap() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        t[i] = new list<Entry *>; 
    }
}

HashMap::~HashMap() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        delete t[i];
    }
}

bool HashMap::contains(string word) {
    int pos = hashCode(word) % TABLE_SIZE;
    return list_contains(*t[pos], word);
}

bool HashMap::put(string word, string v) {
    int pos = hashCode(word) % TABLE_SIZE;
    if(list_contains(*t[pos], word))
        return false;

    Entry *new_entry = new Entry(word, v);
    t[pos]->push_back(new_entry);
    return true;
}

bool HashMap::put(string word, long v) {
    int pos = hashCode(word) % TABLE_SIZE;
    if(list_contains(*t[pos], word))
        return false;

    Entry *new_entry = new Entry(word, v);
    t[pos]->push_back(new_entry);
    return true;
}

bool HashMap::put(string word, double v) {
    int pos = hashCode(word) % TABLE_SIZE;
    if(list_contains(*t[pos], word))
        return false;

    Entry *new_entry = new Entry(word, v);
    t[pos]->push_back(new_entry);
    return true;
}

bool HashMap::put(string word, bool v) {
    int pos = hashCode(word) % TABLE_SIZE;
    if(list_contains(*t[pos], word))
        return false;

    Entry *new_entry = new Entry(word, v);
    t[pos]->push_back(new_entry);
    return true;
}

bool HashMap::put(string word, char v) {
    int pos = hashCode(word) % TABLE_SIZE;
    if(list_contains(*t[pos], word))
        return false;

    Entry *new_entry = new Entry(word, v);
    t[pos]->push_back(new_entry);
    return true;
}

Entry *HashMap::get(string word) {
    int pos = hashCode(word) % TABLE_SIZE;

    for (auto element = t[pos]->begin(); element != t[pos]->end(); ++element) {
        if ((*element)->name.compare(word) == 0 ) {
            return *element;
        }
    }

    return nullptr;
}

Entry::Entry(string n, string v) {
    name = n;
    val.string_lit = v;
    type = tSTRING;
}

Entry::Entry(string n, long v) {
    name = n;
    val.int_lit = v;
    type = tINT;
}

Entry::Entry(string n, double v) {
    name = n;
    val.float_lit = v;
    type = tFLOAT;
}

Entry::Entry(string n, bool v) {
    name = n;
    val.bool_lit = v;
    type = tBOOL;
}

Entry::Entry(string n, char v) {
    name = n;
    val.byte_lit = v;
    type = tBYTE;
}

bool Entry::operator==(string n) {
    return name.compare(n) == 0;
}

Entry::~Entry() {}
