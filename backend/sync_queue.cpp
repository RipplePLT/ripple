#include "sync_queue.hpp"

/**
 * sync_queue.cpp - 
 *
 * Author: Alexander Roth
 * Date:   2015-04-09
 **/

sync_queue::sync_queue(int size) {
    this->sync_queue;
    this->size = size;
}

sync_queue::~sync_queue() {
    this->sync_queue = nullptr;
    this->size = nullptr;
}

void sync_queue::push(struct update info) {
    sync_queue.push(info);
}

struct update sync_queue::pop() {
    return  sync_queue.pop();

}
