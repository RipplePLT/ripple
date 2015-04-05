#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"


void list_init(linkedlist *list){
	list->start = NULL;
}


void list_add(linkedlist *list, char *word){
	
	int len = strlen(word) + 1;
	char *id = malloc(len);
	memcpy(id, word, len);

	llnode *newNode = malloc(sizeof(llnode));
	newNode->data = id;
	newNode->next = list->start;
	list->start = newNode;
}


int list_remove(linkedlist *list, char *word){
	
	llnode *n = list->start;
	llnode *p = NULL;

	while(n){
		if(strcmp(word, n->data) == 0){
			if(p == NULL)
				list->start = n->next;
			else
				p->next = n->next;
			free(n->data);
			free(n);
			return 1;
		}
		p = n;
		n = n->next;
	}

	return 0;
}


int list_contains(linkedlist *list, char *word){

	llnode *n = list->start;
	while(n){
		if(strcmp(word, n->data) == 0){
			return 1;
		}
		n = n->next;
	}
	return 0;

}


void list_delete(linkedlist *list){
	
	llnode *n = NULL;
	
	while(list->start){
		n = list->start;
		list->start = list->start->next;
		free(n->data);
		free(n);
	}
}