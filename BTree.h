//
// Created by 冰镇西瓜哈 on 2023/6/14.
//
#pragma once
#include <iostream>

template <typename valType>
class BTnode;

template <typename valType>
class BinaryTree;

template <typename valType>
class BTnode {
    friend class BinaryTree<valType>;
public:
    explicit BTnode(const valType& val);

    void insert_value(const valType& val);
    void remove_value(const valType& val, BTnode*& prev);

    void lchild_leaf(BTnode* leaf, BTnode* subtree);

    void preorder(BTnode* pt, std::ostream& os) const;
    void inorder(BTnode* pt, std::ostream& os) const;
    void postorder(BTnode* pt, std::ostream& os) const;
private:
    valType _val;
    int _cnt;
    BTnode *_lchild;
    BTnode *_rchild;
};

template <typename elemType>
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree&);

    void insert(const elemType& elem);
    void remove(const elemType& elem);

    void remove_root();

    bool empty() {return _root == 0;}
    void clear() {if(_root) clear(_root); _root = 0;}

    void clear(BTnode<elemType>* pt);
private:
    BTnode<elemType> *_root;

    void copy(BTnode<elemType>* tar, BTnode<elemType>* src);
};

template <typename elemType>
inline BinaryTree<elemType>::BinaryTree():_root(0) {}

template <typename elemType>
inline BinaryTree<elemType>::BinaryTree(const BinaryTree& rhs) {
    copy(_root, rhs);
}

template <typename elemType>
inline BinaryTree<elemType>::~BinaryTree() {
    clear();
}

template <typename elemType>
inline BinaryTree<elemType>& BinaryTree<elemType>::operator=(const BinaryTree& rhs) {
    if(this != &rhs) {
        clear();
        copy(_root, rhs._root);
    }
    return *this;
}

template <typename valType>
inline BTnode<valType>::BTnode(const valType &val):_val(val) {
    _cnt = 1;
    _lchild = _rchild = 0;
}

template <typename elemType>
inline void BinaryTree<elemType>::insert(const elemType &elem) {
    if (!_root) {
        _root = new BTnode<elemType>(elem);
    } else {
        _root->insert_value(elem);
    }
}

template <typename elemType>
inline void BinaryTree<elemType>::remove(const elemType &elem) {
if (_root) {
        if (_root->_val == elem) {
            remove_root();
        } else {
            _root->remove_value(elem, _root);
        }
    }
}