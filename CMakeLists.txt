cmake_minimum_required(VERSION 3.15)
project(clion-test)
set(CMAKE_CXX_STANDARD 17)

add_executable(clion-test C++11-test.cpp myVector.h myVector.cpp myListNode.h myList.h myList.cpp myStack.h myStackTest.cpp myQueue.h BinNode.h BinTree.h BinTree.cpp Graph.h GraphMatrix.h GraphMatrix.cpp BST.h BST.cpp AVL.h AVL.cpp)

