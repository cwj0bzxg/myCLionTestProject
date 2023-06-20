//
// Created by 冰镇西瓜哈 on 2023/6/20.
//
#include "AVL.h"

template<typename T>
BinNodePosi(T) AVL<T>::insert(const T &e) {
    BinNodePosi(T)& x = search(e);
    if (x) {
        return x;
    }
    BinNodePosi(T) xx = x = new BinNode<T>(e, _hot);
    ++this->_size;
    for (BinNodePosi(T) g = _hot; g; g = g->parent) {
        if (!AvlBalanced(*g)) {
            FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
            break;
        } else {
            this->updateHeight(g);
        }
    }
    return xx;
}

template<typename T>
bool AVL<T>::remove(const T &e) {
    BinNodePosi(T)& x = search(e);
    if (!x) {
        return false;
    }
    removeAt(x, _hot);
    --this->_size;
    for (BinNodePosi(T) g = _hot; g; g = g->parent) {
        if (!AvlBalanced(*g)) {
            g = FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
        }
        this->updateHeight(g);
    }
    return true;
}
