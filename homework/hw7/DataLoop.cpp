// Edgar Robitaille
// erobita1
#include <iostream>

#include "DataLoop.h"

/* Create the default constructor with null pointer and zero count. */
DataLoop::DataLoop() : start(nullptr), count(0) {}

/* Create the non-default constructor which takes integer input and one element data loop. */
DataLoop::DataLoop(const int &num) : count(1) {
    // Create a new Node with null pointers and set them accordingly.
    start = new _Node({num, nullptr, nullptr});
    start->next = start;
    start->prev = start;
}

DataLoop::DataLoop(const DataLoop & rhs) {
    if (rhs.count == 0) {
        return;
    }

    start = new _Node{rhs.start->data, nullptr, nullptr};
    start->next = start;
    start->prev = start;

    _Node *current = rhs.start->next;
    _Node *newNode, *prevNode = start;
    while (current != rhs.start) {
        newNode = new _Node{current->data, prevNode, nullptr};
        prevNode->next = newNode;
        current = current->next;
        prevNode = newNode;
    }

    prevNode->next = start;
    start->prev = prevNode;

}

/* Create the destructor which will deallocate dynamically allocatd memory by deletion. */
DataLoop::~DataLoop() {
    // First make sure count is greater than zero, then iterate through and deallocate nodes.
    if (count > 0) {
        _Node* currentNode = start;
        _Node* nextNode;

        for (size_t i = 0; i < count; ++i) {
            nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }

        start = nullptr;
        count = 0;
    }
}

DataLoop & DataLoop::operator=(const DataLoop & rhs) {
    
}

bool DataLoop::operator==(const DataLoop & rhs) const {

}

DataLoop & DataLoop::operator+=(const int & num) {

}

DataLoop DataLoop::operator+(const DataLoop & rhs) const {

}

DataLoop & DataLoop::operator^(int offset) {

}

DataLoop & DataLoop::splice(DataLoop & rhs, size_t pos) {
    
}