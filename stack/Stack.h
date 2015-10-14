#ifndef __STACK_H
#define __STACK_H

#include <iostream>

template <typename T>
class Stack {			//ABSTRACT CLASS
public:
	virtual void push(const T &item) = 0;		//pure virtual
	virtual void pop(T &item) = 0;              //pure virtual
    virtual ~Stack() = 0;                       //pure virtual
	virtual bool isEmpty() const = 0;           //pure virtual
	virtual bool isFull() const = 0;            //pure virtual

	void top(T& item) const
	{
#ifdef DEBUG
        std::cout << "Stack: top" << std::endl;
#endif
		pop(item);
		push(item);
	}
};

template <typename T>
Stack<T>::~Stack()
{
#ifdef DEBUG
    std::cout << "Stack: destructor" << std::endl;
#endif
}

#endif