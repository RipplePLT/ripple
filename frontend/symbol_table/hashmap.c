#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "linkedlist.h"
#include "hashmap.h"


int hashCode(const char *word) {
    
    int h = 0;
    int length = strlen(word);
    
    if (length > 0) {
        int i;
        for (i = 0; i < length; i++) {
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


struct hashmap *hashmap_init(){
	
	hashmap *map = malloc(sizeof(hashmap));
	memset(map, 0, sizeof(hashmap));

	map->table = malloc(DEFAULT_TABLE_SIZE * sizeof(struct linkedlist));
	int i;
	for(i = 0; i < DEFAULT_TABLE_SIZE; i++)
		list_init(&map->table[i]);

	return map;
}


void hashmap_destroy(hashmap *map){
	
	int i;
	for(i = 0; i < DEFAULT_TABLE_SIZE; i++)
		list_delete(&map->table[i]);
	free(map->table);
	free(map);
}


char *hashmap_put(hashmap *map, char *word){

	int position = hashCode(word) % DEFAULT_TABLE_SIZE;
	if(list_contains(&map->table[position], word))
		return NULL;

	return list_add(&map->table[position], word);
}


int hashmap_contains(hashmap *map, char *word){
	int position = hashCode(word) % DEFAULT_TABLE_SIZE;
	return list_contains(&map->table[position], word);
}


int hashmap_remove(hashmap *map, char *word){
	int position = hashCode(word) % DEFAULT_TABLE_SIZE;
	return list_remove(&map->table[position], word);
}