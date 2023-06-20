//
// Created by 冰镇西瓜哈 on 2023/6/20.
//
#pragma once
#include "BinTree.h"

template<typename T>
struct Entry {
    T key;
    int value;
    Entry(T k = T(), int v = 0) : key(k), value(v) {}
    Entry(Entry<T> const& e) : key(e.key), value(e.value) {}
    bool operator<(Entry<T> const& e) { return key < e.key; }
    bool operator>(Entry<T> const& e) { return key > e.key; }
    bool operator==(Entry<T> const& e) { return key == e.key; }
    bool operator!=(Entry<T> const& e) { return key != e.key; }
};

template<typename T>
class BST : public BinTree<T> {
protected:
    BinNodePosi(T) _hot;
    BinNodePosi(T) connect34(
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);
public:
    virtual BinNodePosi(T) & search(const T& e);
    virtual BinNodePosi(T) insert(const T& e);
    virtual bool remove(const T& e);
};

