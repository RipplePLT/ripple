#ifndef _HASHMAP_
#define _HASHMAP_

#define HASH_PRIME 31

#define DEFAULT_TABLE_SIZE 997

struct hashmap{
	struct linkedlist *table;
};

typedef struct hashmap hashmap;

hashmap *hashmap_init();
void hashmap_destroy(hashmap *map);
char *hashmap_put(hashmap *map, char *word);
int hashmap_contains(hashmap *map, char *word);
int hashmap_remove(hashmap *map, char *word);

#endif