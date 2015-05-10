#include "sync_test.h"

int main() {

    // Set up
    sync_queue tester;

    // Initialization tests
    cout << "Initialization Tests" << endl;
    cout << "======================================================" << endl;
    
    test_sync_queue_creation();
    test_empty_queue_creation(tester);

    cout << "Current queue size:\t" << tester.get_size() << endl;
    cout << endl;

    // Adding to queue tests
    cout << "Insertion Tests" << endl;
    cout << "======================================================" << endl;

    test_add_one_to_queue(tester);
    test_add_multiples_to_queue(tester);

    cout << "Current queue size:\t" << tester.get_size() << endl;
    cout << endl;

    // Remove from queue.
    cout << "Removal Tests" << endl;
    cout << "======================================================" << endl;

    test_remove_one_from_queue(tester);
    test_remove_all_from_queue(tester);

    cout << "Current queue size:\t" << tester.get_size() << endl;
    cout << endl;

    // Mixed Pushs and Pops Test.
    cout << "Mix Tests" << endl;
    cout << "======================================================" << endl;

    test_push_pop_mix(tester);

    cout << "Current queue size:\t" << tester.get_size() << endl;
    cout << endl;

    // Test if Empty
    cout << "Clear Tests" << endl;
    cout << "======================================================" << endl;

    test_queue_is_empty(tester);

    cout << "Current queue size:\t" << tester.get_size() << endl;
    cout << endl;

    cout << "All tests passed" << endl;

    return 0;
}

void test_sync_queue_creation() {
    sync_queue test(1);
    assert(test.get_size() == 1);
}

void test_empty_queue_creation(sync_queue& test) {
    assert(test.get_size() == 0);
    assert(test.empty());
}

void test_add_one_to_queue(sync_queue& test) {
    int check = test.get_size();

    struct update test_info = create_test_info();

    cout << "Size before push:\t" << check << endl;
    test.push(test_info);
    cout << "Size after push:\t" << test.get_size() << endl;
    ++check;
    assert(test.get_size() == check);
}

static struct update create_test_info() {
    struct update test_info;

    int x = 10;
    test_info.address = &x;
    test_info.new_value = create_test_link_val();

    return test_info;
}

static link_val create_test_link_val() {
    link_val test_val;
    test_val.type = ltINT;
    test_val.value.intval = 5;

    return test_val;
}

void test_add_multiples_to_queue(sync_queue& test) {
    int check = test.get_size();

    cout << "Size before pushs:\t" << check << endl;

    for (int i = 0; i < 100; ++i) {
        struct update test_info = create_test_info();
        test.push(test_info);
        ++check;
    }

    cout << "Size after pushs:\t" << test.get_size() << endl;

    assert(test.get_size() == check);
}

void test_remove_one_from_queue(sync_queue& test) {
    int check = test.get_size();

    cout << "Size before pop:\t" << check << endl;
    struct update test_info = test.pop();
    cout << "Address of test_info:\t" << test_info.address << endl;
    --check;
    cout << "Size after pop:  \t" << test.get_size() << endl;

    assert(test.get_size() == check);
}

void test_remove_all_from_queue(sync_queue& test) {

    cout << "Size before pop all:\t" << test.get_size() << endl;

    while (!test.empty()) {
        test.pop();
    }

    cout << "Size after pop all:\t" << test.get_size() << endl;

    assert(test.get_size() == 0);
    assert(test.empty());
}

void test_push_pop_mix(sync_queue& test) {
    int check = test.get_size();

    cout << "Size before mix:\t" << check << endl;

    for (int i = 0; i < 100; ++i) {
        struct update test_info = create_test_info();
        test.push(test_info);
        test.pop();
    }

    cout << "Size after mixing:\t" << test.get_size() << endl;

    assert(test.get_size() == check);
    assert(test.empty());
}

void test_queue_is_empty(sync_queue& test) {
    assert(test.empty());
}
