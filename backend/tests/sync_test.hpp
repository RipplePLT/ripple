#ifndef SYNC_TEST_HPP
#define SYNC_TEST_HPP

#include "../expression_tree.hpp"
#include "../link_val.hpp"

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
