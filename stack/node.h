#ifndef __NODE_H
#define __NODE_H

#include "LStack.h"

#include <iostream>

template <typename T>

class Node{
    template <typename A> friend class LStack;
public:
	Node(const T& v, Node<T> *n = nullptr):value_(v),next_(n)
    {
#ifdef DEBUG
        std::cout << "Node: constructor" << std::endl;
#endif
    }
    ~Node()
    {
#ifdef DEBUG
        std::cout << "Node: destructor" << std::endl;
#endif
    }
private:
	T value_;
	Node<T>* next_;
};

#endif