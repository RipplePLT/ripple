#include "sync_queue.hpp"

sync_queue::sync_queue() {
    this->size = 0;
    update_queue = new queue<struct update>;
}

sync_queue::sync_queue(int size) {
    this->size = size;
    update_queue = new queue<struct update>;
}

sync_queue::~sync_queue() {
    delete update_queue;
    this->size = 0;
}

void sync_queue::push(struct update info) {
    this->update_queue->push(info);
    this->size++;
}

struct update sync_queue::pop() {
    struct update info = update_queue->front();
    this->update_queue->pop();
    this->size--;
    return info;
}

bool sync_queue::empty() {
    return ((this->size == 0) && update_queue->empty()) ? true : false;
}

int sync_queue::get_size() {
    return this->size;
}
