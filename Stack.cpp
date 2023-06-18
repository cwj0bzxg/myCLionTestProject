//
// Created by 冰镇西瓜哈 on 2023/6/13.
//
#include "Stack.h"

bool Stack::push(const std::string &elem) {
    if(full())
        return false;
    _stack.push_back(elem);
    return true;
}

bool Stack::pop(std::string &elem) {
    if(empty())
        return false;
    elem = _stack.back();
    _stack.pop_back();
    return true;
}

bool Stack::peek(std::string &elem) {
    if(empty())
        return false;
    elem = _stack.back();
    return true;
}

bool Stack::empty() {
    return _stack.empty();
}

bool Stack::full() {
    return _stack.size() == _stack.max_size();
}

Stack &Stack::operator=(const Stack &rhs) {
    if (this != &rhs) {
        _stack = rhs._stack;
    }
    return *this;
}

Stack::size_type Stack::size() {
    return _stack.size();
}


