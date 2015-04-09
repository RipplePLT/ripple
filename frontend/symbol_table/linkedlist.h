#ifndef _LINKEDLIST_
#define _LINKEDLIST_

struct llnode{
	char *data;
	struct llnode *next;
};

struct linkedlist{
	struct llnode *start;
};

typedef struct linkedlist linkedlist;
typedef struct llnode llnode;


void list_init(struct linkedlist *list);
char *list_add(struct linkedlist *list, char *word);
int list_contains(struct linkedlist *list, char *word);
int list_remove(struct linkedlist *list, char *word);
void list_delete(struct linkedlist *list);


#endif