//
// Created by 冰镇西瓜哈 on 2023/6/19.
//
#include "myStack.h"

// 括号匹配检查
bool paren(const char exp[], int lo, int hi) {
    myStack<char> S;
    for (int i = lo; lo <= hi; i++)
        switch (exp[i]) {
            case '(':
            case '[':
            case '{':
                S.push(exp[i]);
                break;
            case ')':
                if ((S.empty()) || ('(' != S.pop())) {
                    return false;
                }
                break;
            case ']':
                if ((S.empty()) || ('[' != S.pop())) {
                    return false;
                }
                break;
            case '}':
                if ((S.empty()) || ('{' != S.pop())) {
                    return false;
                }
                break;
            default:
                break;
        }
    return S.empty();
}