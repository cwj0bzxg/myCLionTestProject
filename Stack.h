//
// Created by 冰镇西瓜哈 on 2023/6/13.
//
#pragma once

#include <string>
#include <vector>

class Stack;

class Stack {
public:
    typedef int size_type;
    typedef bool (*P)(std::string &elem);
    Stack() = default;
    Stack(const Stack& rhs) = default;
    ~Stack() = default;

    bool push(const std::string &);
    bool pop(std::string &elem);
    bool peek(std::string &elem);

    bool empty();
    bool full();

    size_type size();

    Stack& operator=(const Stack& rhs);
private:
    std::vector<std::string> _stack;
};
