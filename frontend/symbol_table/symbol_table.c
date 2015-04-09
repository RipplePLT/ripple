#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

void symbol_table_init(symbol_table *st){

	st->start = NULL;
	st->current = NULL;
}


void symbol_table_scope_in(symbol_table *st, int line_no){

	symbol_table_node *node = malloc(sizeof(symbol_table_node));

	node->hashmap = hashmap_init();
	node->child = NULL;
	if(!st->start){
		st->start = node;
		node->sibling = node->parent = NULL;
	} else {
		node->parent = st->current;
		node->sibling = st->current->child;
		st->current->child = node;
	}

	st->current = node;

}


void symbol_table_scope_out(symbol_table *st, int line_no){

	if(st->current->parent){
		st->current = st->current->parent;
		return;
	}

	symbol_table_node *node = malloc(sizeof(symbol_table_node));

	node->hashmap = hashmap_init();
	node->child = node->parent = node->sibling = NULL;
	st->current->sibling = node;
	st->current = node;
}


char *symbol_table_put(symbol_table *st, char *word){
	return hashmap_put(st->current->hashmap, word);
}


int symbol_table_contains(symbol_table *st, char *word){
	
	symbol_table_node *n = st->current;
	while(n){
		if(hashmap_contains(n->hashmap, word))
			return 1;
		n = n->parent;
	}
	return 0;
}


int symbol_table_remove(symbol_table *st, char *word){
	return hashmap_remove(st->current->hashmap, word);
}


void symbol_table_destroy_node(symbol_table_node *node){

	if(!node)
		return;

	symbol_table_destroy_node(node->child);
	
	symbol_table_node *n = node->sibling;
	symbol_table_node *next;
	while(n){
		next = n->sibling;
		symbol_table_destroy_node(n);
		n = next;
	}

	hashmap_destroy(node->hashmap);
	free(node);

}


void symbol_table_destroy(symbol_table *st){
	symbol_table_destroy_node(st->start);
}