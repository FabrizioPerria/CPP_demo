#ifndef __LSTACK_H
#define __LSTACK_H

#include <iostream>
#include "Stack.h"
#include "node.h"

template <typename T> class Node;

template <typename T>
class LStack : public Stack<T> {
public:
    LStack();
    
    LStack(const LStack& rhs);
    
    LStack& operator=(const LStack& rhs);
    
    ~LStack();
    
    virtual void push(const T& item);
    
    virtual void pop(T& item);
    
    virtual bool isEmpty() const;
    
    virtual bool isFull() const;
    
private:
	Node<T> *head_;
};

#endif