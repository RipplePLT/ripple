#ifndef _SYMBOL_TABLE_
#define _SYMBOL_TABLE_

#include "hashmap.h"
#include "linkedlist.h"

struct symbol_table_node{
	struct hashmap *hashmap;
	struct symbol_table_node *sibling;
	struct symbol_table_node *child;
	struct symbol_table_node *parent;
};

struct symbol_table{
	struct symbol_table_node *start;
	struct symbol_table_node *current;
};

typedef struct symbol_table symbol_table;
typedef struct symbol_table_node symbol_table_node;

void symbol_table_init(symbol_table *st);

void symbol_table_scope_in(symbol_table *st, int line_no);
void symbol_table_scope_out(symbol_table *st, int line_no);

char *symbol_table_put(symbol_table *st, char *word);
int symbol_table_contains(symbol_table *st, char *word);
int symbol_table_remove(symbol_table *st, char *word);

void symbol_table_destroy(symbol_table *st);


#endif