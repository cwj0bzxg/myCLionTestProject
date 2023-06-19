//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#include "myVector.h"

template<typename T>
class myStack : public myVector<T> {
public:
    void push(T const& e) {
        this->insert(this->size(), e);
    }
    T pop() {
        return this->remove(this->size() - 1);
    }
    T& top() {
        return (*this)[this->size() - 1];
    }
};
