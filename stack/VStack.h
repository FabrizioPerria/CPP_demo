#ifndef __VSTACK_H
#define __VSTACK_H

#include "Stack.h"
#include <iostream>

#include <vector>

using namespace std;

template <typename T>
class VStack : public Stack<T> {
public:
    VStack(int s = 0);
    
    VStack(const VStack<T>& rhs);
	
    VStack<T> operator=(const VStack<T>& rhs);
    
    ~VStack();
	
    virtual void push(const T& item);
    
    virtual void pop(T& item);
    
    virtual bool isEmpty() const;
	
    virtual bool isFull() const;
    
private:
    vector<T> stack_;
	int top_;
};



#endif