//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#pragma once
#include "myList.h"

template<typename T>
class myQueue : public myList<T> {
public:
    void enqueue(T const& e) {
        this->insertAsLast(e);
    }
    T dequeue() {
        return this->remove(this->first());
    }
    T& front() {
        return this->first()->data;
    }
};
