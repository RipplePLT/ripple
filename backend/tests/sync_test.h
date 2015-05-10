#ifndef __SYNC_TEST_H__
#define __SYNC_TEST_H__

#include <assert.h>
#include <iostream>

#include "../expression_tree.h"
#include "../link_val.h"
#include "../sync_queue.h"

void test_sync_queue_creation();
void test_empty_queue_creation(sync_queue& test);
void test_add_one_to_queue(sync_queue& test);
void test_add_multiples_to_queue(sync_queue& test);
void test_remove_one_from_queue(sync_queue& test);
void test_remove_all_from_queue(sync_queue& test);
void test_push_pop_mix(sync_queue& test);
void test_queue_is_empty(sync_queue& test);

static struct update create_test_info();
static link_val create_test_link_val();

#endif
