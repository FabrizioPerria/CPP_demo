#ifndef __LSTACK_CPP
#define __LSTACK_CPP

#include "LStack.h"

template <typename T>
inline LStack<T>::LStack() : head_(nullptr)
{
#ifdef DEBUG
    std::cout << "LStack: constructor" << std::endl;
#endif
}

template <typename T>
LStack<T>::LStack(const LStack& rhs): head_(rhs.head_)
{
#ifdef DEBUG
    std::cout << "LStack: copy constructor" << std::endl;
#endif
}

template <typename T>
LStack<T>& LStack<T>::operator=(const LStack& rhs)
{
    LStack tmp;
#ifdef DEBUG
    std::cout << "LStack: assignment operator" << std::endl;
#endif
    tmp.top_ = rhs.top_;
    tmp.head_ = rhs.head_;
    return tmp;
}

template <typename T>
LStack<T>::~LStack()
{
    // delete all the nodes one by one
    Node<T> *tmp = this->head_;
#ifdef DEBUG
    std::cout << "LStack: destructor" << std::endl;
#endif
    while(head_ != nullptr){
        head_ = head_->next_;
        delete tmp;
        tmp = head_;
    }
}

template <typename T>
void LStack<T>::push(const T& item)
{
    // Create a new node
    Node<T> *tmp = new Node<T>(item);
#ifdef DEBUG
    std::cout << "LStack: push" << std::endl;
#endif
    
    //fill the fields
    tmp->value_ = item;
    tmp->next_ = head_;
    
    //insert in the head
    head_ = tmp;
}

template <typename T>
void LStack<T>::pop(T& item)
{
    //take the item in a temp
    Node<T> *tmp = head_;
#ifdef DEBUG
    std::cout << "LStack: pop" << std::endl;
#endif
    //increment head
    head_ = head_->next_;
    item = tmp->value_;
    //delete the item
    delete tmp;
}

template <typename T>
bool LStack<T>::isEmpty() const
{
#ifdef DEBUG
    std::cout << "LStack: isEmpty" << std::endl;
#endif
    return this->head_ == nullptr;
}

template <typename T>
bool LStack<T>::isFull() const
{
#ifdef DEBUG
    std::cout << "LStack: isFull" << std::endl;
#endif
    return false;    //this is a list, there's no virtual limit to the stack.....
}


#endif