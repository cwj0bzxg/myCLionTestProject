//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#include "myVector.h"
#include <cstdlib>
#include <functional>

template<typename T>
void myVector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

template<typename T>
myVector<T>& myVector<T>::operator=(myVector<T> const& V) {
    if (_elem) {
        delete[] _elem;
    }
    copyFrom(V._elem, 0, V.size()); // _elem是protected类型的，所以可以直接访问
    return *this;
}

template<typename T>
void myVector<T>::expand() {
    if (_size < _capacity) {
        return;
    }
    if (_capacity < DEFAULT_CAPACITY) {
        _capacity = DEFAULT_CAPACITY;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template<typename T>
void myVector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) {
        return;
    }
    if (_size << 2 > _capacity) {
        return;
    }
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; ++i) {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

template<typename T>
T& myVector<T>::operator[](Rank r) const {
    return _elem[r];
}

template<typename T>
void permute(myVector<T>& V) {
    for (int i = V.size(); i > 0; --i) {
        std::swap(V[i - 1], V[rand() % i]);
    }
}

template<typename T>
void myVector<T>::unsort(Rank lo, Rank hi) {
    T* V = _elem + lo;
    for (Rank i = hi - lo; i > 0; --i) {
        std::swap(V[i - 1], V[rand() % i]);
    }
}

template<typename T>
static bool lt(T* a, T* b) {
    return lt(*a, *b);  // 前面没定义这个函数，为什么可以调用？
}

template<typename T>
static bool lt(T& a, T& b) {
    return a < b;
}

template<typename T>
static bool eq(T* a, T* b) {
    return eq(*a, *b);
}

template<typename T>
static bool eq(T& a, T& b) {
    return a == b;
}

template<typename T>
Rank myVector<T>::find(T const& e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

template<typename T>
Rank myVector<T>::insert(Rank r, T const& e) {
    expand();
    for (int i = _size; i > r; --i) {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    ++_size;
    return r;
}

template<typename T>
int myVector<T>::remove(Rank lo, Rank hi) {
    if (lo == hi) {
        return 0;
    }
    while (hi < _size) {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
T myVector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template<typename T>
int myVector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while (i < _size) {
        (find(_elem[i], 0, i) < 0) ? ++i : remove(i);
    }
    return oldSize - _size;
}

template<typename T>
void myVector<T>::traverse(void (*visit)(T &)) {
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template<typename T>
template<typename VST>
void myVector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template<typename T>
struct Increase {
    virtual void operator()(T &e) { // 为什么要加virtual？
        e++;
    }
};

template<typename T>
void increase(myVector<T> &V) {
    V.traverse(Increase<T>());
}

template<typename T>
int myVector<T>::disordered() const {
    int n = 0;
    for (int i = 1; i < _size; ++i) {
        if (_elem[i - 1] > _elem[i]) {
            ++n;
        }
    }
    return n;
}

template<typename T>
int myVector<T>::uniquify() {
    Rank i = 0,j = 0;
    while(++j < _size) {
        if (_elem[i] != _elem[j])
            _elem[++i] = _elem[j];
    }
    _size = ++i; shrink();
    return j - i;
}

template<typename T>
Rank myVector<T>::search(T const &e, Rank lo, Rank hi) const {
    return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template<typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
    while(lo < hi) {
        Rank mi = (lo + hi) >> 1;
        (e < A[mi])? hi = mi : lo = mi - 1;
    }
    return --lo;
}

template<typename T>
void myVector<T>::bubbleSort(Rank lo, Rank hi) {
    while(!bubble(lo, hi--));
}

template<typename T>
bool myVector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;
    while(++lo < hi) {
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            std::swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;
}

template<typename T>
void myVector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2) {
        return;
    }
    int mi = (lo + hi) >> 1;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

template<typename T>
void myVector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo;
    int lb = mi - lo;
    T* B = new T[lb];
    for (Rank i = 0; i < lb; ++i) {
        B[i] = A[i];
    }
    int lc = hi - mi;
    T* C = _elem + mi;
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
        if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) {
            A[i++] = B[j++];
        }
        if ((k < lc) && (!(j < lb) || (C[k] < B[j]))) {
            A[i++] = C[k++];
        }
    }
    delete[] B;
}
