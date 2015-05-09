#include <cmath>
#include <iostream>
#include "hashmap.h"
#include "../../structures/enum.h"

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

bool HashMap::put(string word, e_type v, int line_no, e_symbol_type s = tNOSTYPE){
    int pos = hashCode(word) % TABLE_SIZE;
    if(list_contains(*t[pos], word)) {
        return false;   
    }

    Entry *new_entry = new Entry(word, v, line_no, s);
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

Entry::Entry(string n, e_type v, int line, e_symbol_type s = tNOSTYPE) {
    name = n;
    type = v;
    line_no = line;
    symbol_type = s;
}

Entry::Entry(string n, int line) {
    name = n;
    type = tNOTYPE;
    line_no = line;
    symbol_type = tNOSTYPE;
}

void Entry::classify(e_symbol_type s) {
    symbol_type = s;
}

void Entry::add_args(list<e_type> *a) {
    args = a;
}


bool Entry::operator==(string n) {
    return name.compare(n) == 0;
}

Entry::~Entry() {}
