//
// Created by 冰镇西瓜哈 on 2023/6/13.
//

#include <iostream>
#include <memory>
#include <exception>
#include <sstream>
#include "Stack.h"

using namespace std;

class iterator_overflow : public exception {
public:
    iterator_overflow(int index, int max) : _index(index), _max(max) {
        _p = new int[1000];
    }
    ~iterator_overflow() override {
        delete _p;
    }

    int index() const { return _index; }
    int max() const { return _max; }

    const char* what() const noexcept override;
private:
    int _index;
    int _max;
    int* _p;
};

const char* iterator_overflow::what() const noexcept {
    ostringstream  ex_msg;
    static string msg;

    ex_msg << "iterator overflow: " << _index << " >= " << _max;

    msg = ex_msg.str();

    return msg.c_str();
}

int main() {
    unique_ptr<exception> aps(new iterator_overflow(10, 5));
    cout << aps->what() << endl;

    return 0;
}
