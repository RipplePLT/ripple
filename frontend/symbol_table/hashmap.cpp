#include <cmath>
#include "hashmap.h"

using namespace std;

int list_contains(list<string> l, string word) {
    for (auto element = l.begin(); element != l.end(); ++element) {
        if (*element == word) {
            return 1;
        }
    }
    return 0;
}

int hashCode(const string word) {

    int h = 0;

    if (word.length() > 0) {
        int i;
        for (i = 0; i < word.length(); i++) {
            h = HASH_PRIME * h + word[i];
        }
    }

    return abs(h);
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
        t[i] = new list<string>; 
    }
}

HashMap::~HashMap() {
    for(int i = 0; i < TABLE_SIZE; i++) {
        delete t[i];
    }
}

string HashMap::put(string word) {
    int pos = hashCode(word) % TABLE_SIZE;
    if(list_contains(*t[pos], word))
        return NULL;

    t[pos]->push_back(word);
    return word;
}

bool HashMap::contains(string word) {
    int pos = hashCode(word) % TABLE_SIZE;
    return list_contains(*t[pos], word);
}

bool HashMap::remove(string word) {
    int pos = hashCode(word) % TABLE_SIZE;

    if(!list_contains(*t[pos], word)) {
        return false;
    }
    t[pos]->remove(word);
    return true;
}
