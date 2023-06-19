//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#pragma once

typedef int Rank;
#define ListNodePosi(T) myListNode<T>*

template<typename T>
struct myListNode {
    T data;
    ListNodePosi(T) pred;
    ListNodePosi(T) succ;

    myListNode() {}
    myListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) : data(e), pred(p), succ(s) {}

    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};
