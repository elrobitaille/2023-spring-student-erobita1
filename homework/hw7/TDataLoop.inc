// Edgar Robitaille
// erobita1
#include <iostream>

#include "TDataLoop.h"

/* Create the default constructor with null pointer and zero count. */
template <typename DataType>
TDataLoop<DataType>::TDataLoop() : start(nullptr), count(0) {}

/* Create the non-default constructor which takes (template) ANY type input and one element data loop. */
template <typename DataType>
TDataLoop<DataType>::TDataLoop(const DataType &data) : count(1) {
    start = new _Node({data, nullptr, nullptr});
    start->next = start;
    start->prev = start;
}

/* Create the copy constructor. */
template <typename DataType>
TDataLoop<DataType>::TDataLoop(const TDataLoop<DataType> & rhs) { 
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

/* Overloads the = operator to assign rhs DataLoop to current DataLoop. */
template <typename DataType>
TDataLoop<DataType> & TDataLoop<DataType>::operator=(const TDataLoop<DataType> & rhs) {
    // First check if there is self assigment involved. 
    if (this == &rhs) {
        return *this;
    }

    while (count > 0 && start != nullptr) {
        _Node *temp = start;
        start->prev->next = nullptr;
        start = start->next;
        delete temp;
        count--;
    }
    
    if (rhs.start != nullptr) {
        _Node *current = rhs.start;
        for (size_t i = 0; i < rhs.count; ++i) {
          *this += current->data;
          current = current->next;
        }
    }

    return *this;
}

/* Create the destructor which will deallocate dynamically allocated memory by deletion. */
template <typename DataType>
TDataLoop<DataType>::~TDataLoop() {
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

/* Overloads == operator to check if two DataLoops are the same, returns bool. */
template <typename DataType>
bool TDataLoop<DataType>::operator==(const TDataLoop<DataType> & rhs) const { 
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
template <typename DataType>
TDataLoop<DataType> & TDataLoop<DataType>::operator+=(const DataType & data) {
    // Create a new node with null pointers, then set next and prev pointers if count is zero.
    _Node *newNode = new _Node({data, nullptr, nullptr});
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
template <typename DataType>
TDataLoop<DataType> TDataLoop<DataType>::operator+(const TDataLoop<DataType> & rhs) const {
    // Create a copy of current object. 
    TDataLoop<DataType> current_copy(*this);

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

/* Overload the ^ operator to shift the list by the offset. */
template <typename DataType>
TDataLoop<DataType> & TDataLoop<DataType>::operator^(int offset) {
    // Return the object when count is zero or one, indicating no change.
    if (count <= 1) {
        return *this;
    }

    // If offset is negative, make it positive.
    // Determines if it is faster to go forward or backward through the list.
    int direction = 1;
    // Convert to size_t to avoid a type error. 
    size_t offset_size_t = static_cast<size_t>(offset);
    if (offset_size_t > count / 2) {
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

/* Inserts a DataLoop object into the current DataLoop object at specified position. */
template <typename DataType>
TDataLoop<DataType> & TDataLoop<DataType>::splice(TDataLoop<DataType> & rhs, size_t pos) {
    // If rhs count = zero, return current object.
    if (rhs.count == 0) {
        return *this;
    }

    // Adjust pos if it is greater than count.
    if (pos >= count) {
        pos %= count;
    }

    // Case where insertion is at the beginning of the list.
    if (pos == 0) {
        start->prev->next = rhs.start; // Set last node's next pointer to first node of rhs.
        rhs.start->prev->next = start; // Set last node of rhs to first node of object.
        TDataLoop<DataType>::_Node* temp = start->prev; // Swaps the prev pointers.
        start->prev = rhs.start->prev; 
        rhs.start->prev = temp;
        start = rhs.start;
    // Case where splice operation is not at the beginning of the list.
    } else { 
        TDataLoop<DataType>::_Node* current = start; // Set current to start and iterate until pos. 
        for (size_t i = 1; i < pos; ++i) { 
            current = current->next;
        }
        rhs.start->prev->next = current->next; // Set next and prev pointers of nodes.
        current->next->prev = rhs.start->prev;
        rhs.start->prev = current; 
        current->next = rhs.start;
    }

    // Update count, reset rhs, and return current object.
    count += rhs.count;
    rhs.start = nullptr;
    rhs.count = 0;
    return *this;
}

/* Overloads the << operator to print DataLoop object to ostream. */
template <typename DataType>
std::ostream & operator<<(std::ostream & os, const TDataLoop<DataType> & dl) {
    // If count is zero, print >no values<.
    if (dl.count == 0) {
        os << ">no values<";
    // Otherwise, just print data in the list and start with -> and first data point.
    } else {
        os << "-> " << dl.start->data << " ";
        // Iterate through nodes and print data points <--> in between.
        typename TDataLoop<DataType>::_Node *current = dl.start->next;
        while (current != dl.start) {
            os << "<--> " << current->data << " ";
            current = current->next;
        }
        os << "<-"; // Print last arrow <-. 
    }
    return os; // Return ostream object.
}

