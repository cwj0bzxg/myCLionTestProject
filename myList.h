//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#pragma once
#include "myListNode.h"

template<typename T>
class myList {
private:
    int _size;
    ListNodePosi(T) header;
    ListNodePosi(T) trailer;
protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T), int);
    void merge(ListNodePosi(T)&, int, myList<T>&, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T)&, int);
    void selectionSort(ListNodePosi(T), int);
    void insertionSort(ListNodePosi(T), int);

public:
    myList() { init(); }
    myList(myList<T> const& L);
    myList(myList<T> const& L, Rank r, int n);
    myList(ListNodePosi(T) p, int n);
    ~myList();

    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }
    T& operator[](Rank r) const;
    ListNodePosi(T) first() const { return header->succ; }
    ListNodePosi(T) last() const { return trailer->pred; }
    bool valid(ListNodePosi(T) p) { return p && (trailer != p) && (header != p); }
    int disordered() const;
    ListNodePosi(T) find(T const& e) const { return find(e, _size, trailer); }
    ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) search(T const& e) const { return search(e, _size, trailer); }
    ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
    ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }
    ListNodePosi(T) insertAsFirst(T const& e);
    ListNodePosi(T) insertAsLast(T const& e);
    ListNodePosi(T) insertA(ListNodePosi(T) p, T const& e);
    ListNodePosi(T) insertB(ListNodePosi(T) p, T const& e);
    T remove(ListNodePosi(T) p);
    void merge(myList<T>& L) { merge(first(), size(), L, L.first(), L._size); }
    void sort(ListNodePosi(T) p, int n);
    void sort() { sort(first(), _size); }
    int deduplicate();
    int uniquify();
    void reverse();
    void traverse(void (*)(T&));
    template<typename VST>
    void traverse(VST&);
};
