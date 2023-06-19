//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#include "myList.h"
#include "myListNode.h"
#include <cstdlib>

template<typename T>
void myList<T>::init() {
    header = new myListNode<T>;
    trailer = new myListNode<T>;
    header->succ = trailer;
    header->pred = nullptr;
    trailer->pred = header;
    trailer->succ = nullptr;
    _size = 0;
}

template<typename T>
T& myList<T>::operator[](Rank r) const {
    ListNodePosi(T) p = first();
    while (0 < r--) p = p->succ;
    return p->data;
}

template<typename T>
ListNodePosi(T) myList<T>::find(T const& e, int n, ListNodePosi(T) p) const {
    while (0 < n--)
        if (e == (p = p->pred)->data) return p;
    return nullptr;
}

template<typename T>
ListNodePosi(T) myList<T>::insertAsFirst(T const& e) {
    _size++;
    return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) myList<T>::insertAsLast(T const& e) {
    _size++;
    return trailer->insertAsPred(e);
}

template<typename T>
ListNodePosi(T) myList<T>::insertA(ListNodePosi(T) p, T const& e) {
    _size++;
    return p->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) myList<T>::insertB(ListNodePosi(T) p, T const& e) {
    _size++;
    return p->insertAsPred(e);
}

template<typename T>
ListNodePosi(T) myListNode<T>::insertAsPred(const T &e) {
    ListNodePosi(T) x = new myListNode(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template<typename T>
ListNodePosi(T) myListNode<T>::insertAsSucc(const T &e) {
    ListNodePosi(T) x = new myListNode(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}

template<typename T>
void myList<T>::copyNodes(ListNodePosi(T) p, int n) {
    init();
    while (n--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template<typename T>
myList<T>::myList(ListNodePosi(T) p, int n) {
    copyNodes(p, n);
}

template<typename T>
myList<T>::myList(myList<T> const& L) {
    copyNodes(L.first(), L._size);
}

template<typename T>
myList<T>::myList(myList<T> const& L, Rank r, int n) {
    copyNodes(L[r], n);
}

template<typename T>
T myList<T>::remove(ListNodePosi(T) p) {
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    _size--;
    return e;
}

template<typename T>
myList<T>::~myList() {
    clear();
    delete header;
    delete trailer;
}

template<typename T>
int myList<T>::clear() {
    int oldSize = _size;
    while (0 < _size) remove(header->succ);
    return oldSize;
}

template<typename T>
int myList<T>::deduplicate() {
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = header;
    Rank r = 0;
    while (trailer != (p = p->succ)) {
        ListNodePosi(T) q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - _size;
}

template<typename T>
void myList<T>::traverse(void (*visit)(T&)) {
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template<typename T>
template<typename VST>
void myList<T>::traverse(VST& visit) {
    for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template<typename T>
int myList<T>::uniquify() {
    if (_size < 2) return 0;
    int oldSize = _size;
    ListNodePosi(T) p = first();
    ListNodePosi(T) q;
    while (trailer != (q = p->succ))
        if (p->data != q->data) p = q;
        else remove(q);
    return oldSize - _size;
}

template<typename T>
ListNodePosi(T) myList<T>::search(T const& e, int n, ListNodePosi(T) p) const {
    while (0 <= n--)  // 为什么是0 <= n--而不是0 < n--?
        if (((p = p->pred)->data) <= e) break;
    return p;
}

template<typename T>
void myList<T>::sort(ListNodePosi(T) p, int n) {
    switch (rand() % 3) {
        case 1: insertionSort(p, n); break;
        case 2: selectionSort(p, n); break;
        default: mergeSort(p, n); break;
    }
}

template<typename T>
void myList<T>::insertionSort(ListNodePosi(T) p, int n) {
    for (int r = 0; r < n; r++) {
        insertA(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template<typename T>
void myList<T>::selectionSort(ListNodePosi(T) p, int n) {
    ListNodePosi(T) head = p->pred;
    ListNodePosi(T) tail = p;
    for (int i = 0; i < n; i++) tail = tail->succ;
    while (1 < n) {  // 为什么是1 < n而不是0 < n?
        ListNodePosi(T) max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        n--;
    }
}

template<typename T>
ListNodePosi(T) myList<T>::selectMax(ListNodePosi(T) p, int n) {
    ListNodePosi(T) max = p;
    for (ListNodePosi(T) cur = p; 1 < n; n--)
        if ((cur = cur->succ)->data >= max->data) max = cur;
    return max;
}

template<typename T>
void myList<T>::merge(ListNodePosi(T)& p, int n, myList<T>& L, ListNodePosi(T) q, int m) {
    ListNodePosi(T) pp = p->pred;
    while (0 < m)
        if ((0 < n) && (p->data <= q->data)) {
            if (q == (p = p->succ)) break;
            n--;
        } else {
            insertB(p, L.remove((q = q->succ)->pred));
            m--;
        }
    p = pp->succ;
}

template<typename T>
void myList<T>::mergeSort(ListNodePosi(T)& p, int n) {
    if (n < 2) return;
    int m = n >> 1;
    ListNodePosi(T) q = p;
    for (int i = 0; i < m; i++) q = q->succ;
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);
}
