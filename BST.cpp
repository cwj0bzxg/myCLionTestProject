//
// Created by 冰镇西瓜哈 on 2023/6/20.
//
#include "BST.h"
#include "BinTree.h"
#include "BinNode.h"

template<typename T>
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) {
    if (!v || (e == v->data)) {
        return v;
    }
    hot = v;
    return searchIn(((e < v->data) ? v->lchild : v->rchild), e, hot);
}

template<typename T>
BinNodePosi(T)& BST<T>::search(const T &e) {
    return searchIn(this->_root, e, _hot = nullptr);
}

template<typename T>
BinNodePosi(T) BST<T>::insert(const T &e) {
    BinNodePosi(T)& x = search(e);
    if (x) {
        return x;
    }
    x = new BinNode<T>(e, _hot);
    ++this->_size;
    this->updateHeightAbove(x);
    return x;
}

template<typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot) {
    BinNodePosi(T) w = x;
    BinNodePosi(T) succ = nullptr;
    if (!HasLChild(*x)) {
        succ = x = x->rchild;
    } else if (!HasRChild(*x)) {
        succ = x = x->lchild;
    } else {
        // 这部分的处理值得学习
        w = w->succ();
        swap(x->data, w->data);
        BinNodePosi(T) u = w->parent;
        ((u == x) ? u->rchild : u->lchild) = succ = w->rchild;
    }
    hot = w->parent;
    if (succ) {
        succ->parent = hot;
    }
    release(w->data);
    release(w);
    return succ;
}

template<typename T>
bool BST<T>::remove(const T &e) {
    BinNodePosi(T)& x = search(e);
    if (!x) {
        return false;
    }
    removeAt(x, _hot);
    --this->_size;
    this->updateHeightAbove(_hot);
    return true;
}

template<typename T>
BinNodePosi(T) BST<T>::connect34(BinNode<T> *a, BinNode<T> *b, BinNode<T> *c, BinNode<T> *T0, BinNode<T> *T1, BinNode<T> *T2,
                                 BinNode<T> *T3) {
    a->lc = T0;
    if (T0) {
        T0->parent = a;
    }
    a->rc = T1;
    if (T1) {
        T1->parent = a;
    }
    this->updateHeight(a);
    c->lc = T2;
    if (T2) {
        T2->parent = c;
    }
    c->rc = T3;
    if (T3) {
        T3->parent = c;
    }
    this->updateHeight(c);
    b->lc = a;
    a->parent = b;
    b->rc = c;
    c->parent = b;
    this->updateHeight(b);
    return b;
}

template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNode<T> *v) {
    BinNodePosi(T) p = v->parent;
    BinNodePosi(T) g = p->parent;
    if (IsLChild(*p)) {
        if (IsLChild(*v)) {
            p->parent = g->parent;
            return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
        } else {
            v->parent = g->parent;
            return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
        }
    } else {
        if (IsRChild(*v)) {
            p->parent = g->parent;
            return connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild);
        } else {
            v->parent = g->parent;
            return connect34(g, v, p, g->lchild, v->lchild, v->rchild, p->rchild);
        }
    }
}


