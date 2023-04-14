// Edgar Robitaille
// erobita1
#include <iostream>

#include "DataLoop.h"

DataLoop::DataLoop() : start(nullptr), count(0) {}

DataLoop::DataLoop(const int &num) : count(1) {
    start = new _Node({num, nullptr, nullptr});
    start->next = start;
    start->prev = start;
}

DataLoop::DataLoop(const DataLoop & rhs) {

}

DataLoop::~DataLoop() {
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