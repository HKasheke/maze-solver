#include "stack.h"

Stack::~Stack() {
    while (_top != nullptr) {
        pop();
    }
}

void  Stack::push(const Data& data) {
    const auto node = new Node(data);
    node->_next = _top;
    _top = node;
}

Data* Stack::top() const {
    if (_top == nullptr) return nullptr;
    return &_top->_data;
}

void Stack::pop() {
    if (_top == nullptr)
        return;
    const auto temp = _top;
    _top = _top->_next;
    delete temp;
}