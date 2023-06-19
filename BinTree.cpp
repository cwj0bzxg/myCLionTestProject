//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#include "BinTree.h"
#include "BinNode.h"
#include "myQueue.h"

template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e) {
    _size = 1;
    return _root = new BinNode<T>(e);
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &t) {
    if (x->lc = t->_root) x->lc->parent = x;  // x->lc = t->_root is an assignment, not a comparison
    _size += t->_size;
    updateHeightAbove(x);
    t->_root = nullptr;
    t->_size = 0;
    release(t);
    t = nullptr;
    return x;
}

template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &t) {
    if (x->rc = t->_root) x->rc->parent = x;
    _size += t->_size;
    updateHeightAbove(x);
    t->_root = nullptr;
    t->_size = 0;
    release(t);
    t = nullptr;
    return x;
}

template<typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    _size -= n;
    return n;
}

template<typename T>
static int removeAt(BinNodePosi(T) x) {
    if (!x) return 0;
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data);
    release(x);
    return n;
}

template<typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    BinTree<T>* s = new BinTree<T>;
    s->_root = x;
    x->parent = nullptr;
    s->_size = x->size();
    _size -= s->_size;
    return s;
}

template<typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit) {
    if (!x) return;
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template<typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit) {
    if (!x) return;
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template<typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit) {
    if (!x) return;
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template<typename T>
template<typename VST>
void BinNode<T>::travLevel(VST& visit) {
    myQueue<BinNodePosi(T)> Q;
    Q.enqueue(this);
    while (!Q.empty()) {
        BinNodePosi(T) x = Q.dequeue();
        visit(x->data);
        if (HasLChild(*x)) Q.enqueue(x->lc);
        if (HasRChild(*x)) Q.enqueue(x->rc);
    }
}