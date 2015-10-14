#ifndef __VSTACK_CPP
#define __VSTACK_CPP

#include "VStack.h"

template <typename T>
inline VStack<T>::VStack(int s)  : top_(0), stack_(s)
{
#ifdef DEBUG
    std::cout << "VStack: constructor" << std::endl;
#endif
}

template <typename T>
inline VStack<T>::VStack(const VStack<T>& rhs): top_(rhs.top_), stack_(rhs.stack_)
{
#ifdef DEBUG
    std::cout << "VStack: copy constructor" << std::endl;
#endif
}

template <typename T>
VStack<T> VStack<T>::operator=(const VStack<T>& rhs)
{
#ifdef DEBUG
    std::cout << "VStack: assignment operator" << std::endl;
#endif
    this->top_ = rhs.top_;
    this->stack_ = rhs.stack_;
}

template <typename T>
VStack<T>::~VStack()
{
#ifdef DEBUG
    std::cout << "VStack: destructor" << std::endl;
#endif
}

template <typename T>
void VStack<T>::push(const T& item)
{
#ifdef DEBUG
    std::cout << "VStack: push" << std::endl;
#endif
    this->stack_[this->top_++] = item;
}

template <typename T>
void VStack<T>::pop(T& item)
{
#ifdef DEBUG
    std::cout << "VStack: pop" << std::endl;
#endif
    item = this->stack_[this->top_-1];
}

template <typename T>
bool VStack<T>::isEmpty() const
{
#ifdef DEBUG
    std::cout << "VStack: isEmpty" << std::endl;
#endif
    return this->top_ == 0;
}

template <typename T>
bool VStack<T>::isFull() const
{
#ifdef DEBUG
    std::cout << "VStack: isFull" << std::endl;
#endif
    return this->top_ >= this->stack_.size();
}

#endif