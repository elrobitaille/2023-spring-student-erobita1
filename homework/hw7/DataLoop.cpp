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

/* Create the copy constructor */
DataLoop::DataLoop(const DataLoop & rhs) {
    // If object is empty, create empty DataLoop object and simply return. */
    if (rhs.count == 0) {
        return;
    }

    // Set next and prev pointers to itself after creating new node with null pointers. 
    start = new _Node{rhs.start->data, nullptr, nullptr};
    start->next = start;
    start->prev = start;

    // Then, initialize the pointers. 
    _Node *current = rhs.start->next;
    _Node *newNode = nullptr;
    _Node *prevNode = start;

    // Iterate through the nodes and update accordingly 
    while (current != rhs.start) {
        newNode = new _Node{current->data, prevNode, nullptr};
        prevNode->next = newNode;
        current = current->next;
        prevNode = newNode;
    }

    /* Update for the last new node's pointer to new start node and new start 
       prev pointer to last new node, which will complete the 'circular' list. */  
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
    if (this == &rhs) {
        return *this;
    }

    if (count > 0) {
        _Node* currentNode = start;
        _Node* nextNode;

        for (size_t i = 0; i < count; ++i) {
            nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    count = rhs.count; 
    if (rhs.count == 0) {
        start = nullptr;
        return *this;
    }

    return *this;
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