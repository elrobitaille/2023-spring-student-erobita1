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
        start = nullptr;
        count = 0;
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

    count = 1;

    // Iterate through the nodes and update accordingly 
    while (current != rhs.start) {
        newNode = new _Node{current->data, nullptr, prevNode};
        newNode->prev = prevNode;
        prevNode->next = newNode;
        prevNode = newNode;
        current = current->next;
        count += 1;
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

/* Overloads the = operator to assign rhs DataLoop to current DataLoop. */
DataLoop & DataLoop::operator=(const DataLoop & rhs) {
    // First check if there is self assigment involved. 
    if (this == &rhs) {
        return *this;
    }

    // If count is greater than zero, deallocate memory and delete nodes.
    if (count > 0 && start != nullptr) {
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
    
    // If rhs count is zero then creates empty DataLoop object.
    if (rhs.count == 0) {
        start = nullptr;
        return *this;
    }   

    // Creates a new node with null pointers and sets them accordingly.
    start = new _Node{rhs.start->data, nullptr, nullptr};
    start->next = start;
    start->prev = start;

    // Then, initialize the pointers.
    _Node *current = rhs.start->next;
    _Node *newNode = nullptr;
    _Node *prevNode = start;

    // Iterate through the nodes and update accordingly.
    while (current != rhs.start) {
        newNode = new _Node{current->data, prevNode, nullptr};
        prevNode->next = newNode;
        current = current->next;    
        prevNode = newNode;
    }

    // Update last new node pointer to new start node and new start.
    newNode->next = start;
    newNode->prev = start->prev; 
    start->prev = newNode;

    count = rhs.count;

    return *this;
}

bool DataLoop::operator==(const DataLoop & rhs) const {
    // If the node count is not equal, the objects aren't equal, return false. 
    if (count != rhs.count) {
        return false;
    }

    // If the count is zero, the objects are equal, return true.
    if (count == 0) {
        return true;
    }

    _Node *current = start;
    _Node *rhs_current = rhs.start;
    for (size_t i = 0; i < count; ++i) {
        // If the data is not equal, then objects aren't equal, so return false.
        if (current->data != rhs_current->data) {
            return false;
        }
        current = current->next;
        rhs_current = rhs_current->next;
    }

    return true; // All nodes are equal, return true. 

}

/* Overloads the += operator to add a new node to the end of the list. */
DataLoop & DataLoop::operator+=(const int & num) {
    // Create a new node with null pointers, then set next and prev pointers if count is zero.
    _Node *newNode = new _Node({num, nullptr, nullptr});
    if (count == 0) {
        start = newNode;
        start->next = start;
        start->prev = start;
    // Else if the count is non-zero, insert the new node at the end of the list.
    } else {
        newNode->next = start;
        newNode->prev = start->prev;
        start->prev->next = newNode;
        start->prev = newNode;
    }

    count += 1; // Increment count.  

    return *this;
}

/* Overload the + operator to add DataLoop objects together. */
DataLoop DataLoop::operator+(const DataLoop & rhs) const {
    // Create a copy of current object. 
    DataLoop current_copy(*this);

    // If rhs count zero, this means no change, so return current_copy.
    if (rhs.count == 0) {
        return current_copy;
    }

    // If count is zero, also indicates no change, so return rhs.
    if (count == 0) {
        return rhs;
    }

    // Create a new node, then throughout the loop, add the data to the new node.
    _Node* current = rhs.start;
    for (size_t i = 0; i < rhs.count; ++i) {
        current_copy += current->data;
        current = current->next;
    }

    return current_copy; // Return new DataLoop object.

}

// Overload the ^ operator to shift the list by the offset.
DataLoop & DataLoop::operator^(int offset) {
    // Return the object when count is zero or one, indicating no change.
    if (count <= 1) {
        return *this;
    }

    // If offset is negative, make it positive.
    // Determines if it is faster to go forward or backward through the list.
    int direction = 1;
    if (offset > count / 2) {
        direction = -1;
        offset = count - offset;
    }

    // Iterates through list and updates the start's pointer based on the direction.
    for (int i = 0; i < offset; ++i) {
        if (direction == 1) {
            start = start->next;
        } else {
            start = start->prev;
        }
    }

    return *this; // Return the object. 

}

DataLoop& DataLoop::splice(DataLoop& rhs, size_t pos) {
    if (rhs.count == 0) {
        return *this;
    }

    if (pos >= count) {
        pos %= count;
    }

    if (pos == 0) {
        start->prev->next = rhs.start;
        rhs.start->prev->next = start;
        DataLoop::_Node* temp = start->prev;
        start->prev = rhs.start->prev;
        rhs.start->prev = temp;
        start = rhs.start;
    } else {
        DataLoop::_Node* current = start;
        for (size_t i = 1; i < pos; ++i) {
            current = current->next;
        }
        rhs.start->prev->next = current->next;
        current->next->prev = rhs.start->prev;
        rhs.start->prev = current;
        current->next = rhs.start;
    }

    count += rhs.count;
    rhs.start = nullptr;
    rhs.count = 0;
    return *this;
}

/* Overloads the << operator to print DataLoop object to ostream. */
std::ostream & operator<<(std::ostream & os, const DataLoop & dl) {
    // If count is zero, print >no values<.
    if (dl.count == 0) {
        os << ">no values<";
    // Otherwise, just print data in the list and start with -> and first data point.
    } else {
        os << "-> " << dl.start->data << " ";
        // Iterate through nodes and print data points <--> in between.
        DataLoop::_Node *current = dl.start->next;
        while (current != dl.start) {
            os << "<--> " << current->data << " ";
            current = current->next;
        }
        os << "<-"; // Print last arrow <- .
    }

    return os; // Return ostream object.
    
}