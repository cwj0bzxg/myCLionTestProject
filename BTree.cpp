//
// Created by 冰镇西瓜哈 on 2023/6/14.
//

#include "BTree.h"

template<typename valType>
void BTnode<valType>::insert_value(const valType &val) {
    if (val == _val) {
        ++_cnt;
        return;
    }

    if (val < _val) {
        if (!_lchild) {
            _lchild = new BTnode(val);
        } else {
            _lchild->insert_value(val);
        }
    } else {
        if (!_rchild) {
            _rchild = new BTnode(val);
        } else {
            _rchild->insert_value(val);
        }
    }
}

template<typename valType>
void BTnode<valType>::remove_value(const valType &val, BTnode<valType> *&prev) {
    if (val < _val) {
        if (!_lchild) {
            return;
        } else {
            _lchild->remove_value(val, _lchild);
        }
    } else if (val > _val) {
        if (!_rchild) {
            return;
        } else {
            _rchild->remove_value(val, _rchild);
        }
    } else {
        if (_rchild) {
            prev = _rchild;
            if (_lchild) {
                if (!prev->_lchild) {
                    prev->_lchild = _lchild;
                } else {
                    BTnode<valType> *tmp = prev->_lchild;
                    while (tmp->_lchild) {
                        tmp = tmp->_lchild;
                    }
                    tmp->_lchild = _lchild;
                }
            }
        } else {
            prev = _lchild;
        }
        delete this;
    }
}

template<typename valType>
void BTnode<valType>::lchild_leaf(BTnode<valType> *leaf, BTnode<valType> *subtree) {
    while(subtree->_lchild) {
        subtree = subtree->_lchild;
    }
    subtree->_lchild = leaf;
}

template<typename elemType>
void BinaryTree<elemType>::remove_root() {
    if (!_root) {
        return;
    }

    BTnode<elemType> *tmp = _root;
    if (_root->_rchild) {
        _root = _root->_rchild;
        if (tmp->_lchild) {
            BTnode<elemType> *lc = tmp->_lchild;
            BTnode<elemType> *newlc = _root->_lchild;
            if (!newlc) {
                _root->_lchild = lc;
            } else {
                newlc->lchild_leaf(lc, newlc);
            }
        }
    } else {
        _root = _root->_lchild;
    }
    delete tmp;
}

template<typename elemType>
void BinaryTree<elemType>::clear(BTnode<elemType> *pt) {
    if (pt) {
        clear(pt->_lchild);
        clear(pt->_rchild);
        delete pt;
    }
}

template<typename valType>
void BTnode<valType>::preorder(BTnode<valType> *pt, std::ostream &os) const {
    if (pt) {
        os << pt->_val << " ";
        preorder(pt->_lchild, os);
        preorder(pt->_rchild, os);
    }
}

template<typename valType>
void BTnode<valType>::inorder(BTnode<valType> *pt, std::ostream &os) const {
    if (pt) {
        inorder(pt->_lchild, os);
        os << pt->_val << " ";
        inorder(pt->_rchild, os);
    }
}

template<typename valType>
void BTnode<valType>::postorder(BTnode<valType> *pt, std::ostream &os) const {
    if (pt) {
        postorder(pt->_lchild, os);
        postorder(pt->_rchild, os);
        os << pt->_val << " ";
    }
}

template<typename elemType>
void BinaryTree<elemType>::copy(BTnode<elemType> *tar, BTnode<elemType> *src) {
    if (src) {
        tar = new BTnode<elemType>(src->_val);
        if (src->_lchild) {
            copy(tar->_lchild, src->_lchild);
        }
        if (src->_rchild) {
            copy(tar->_rchild, src->_rchild);
        }
    }
}