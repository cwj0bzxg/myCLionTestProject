//
// Created by 冰镇西瓜哈 on 2023/6/20.
//
#pragma once

#include "BST.h"

template<typename T>
class AVL : public BST<T> {
public:
    BinNodePosi(T) insert(const T& e);
    bool remove(const T& e);
};

#define Balanced(x) (stature((x).lchild) == stature((x).rchild))
#define BalFac(x) (stature((x).lchild) - stature((x).rchild))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))

#define tallerChild(x) ( \
    stature((x)->lchild) > stature((x)->rchild) ? (x)->lchild : ( \
    stature((x)->lchild) < stature((x)->rchild) ? (x)->rchild : ( \
    IsLChild(*(x)) ? (x)->lchild : (x)->rchild \
    ) \
    ) \
)