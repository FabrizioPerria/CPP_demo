#include <iostream>
#define DEBUG
#include "VStack.h"
#include "VStack.cpp"

#include "LStack.cpp"
#include "LStack.h"

using namespace std;

//Factory method to create 2 kind of stacks depending on the input parameter
template <typename T>
Stack<T>* make_stack (bool useVector)
{
    if (useVector)
        return new VStack<T>(50);
    else
        return new LStack<T>();
}


int main()
{
    Stack<int> *v = make_stack<int>(true);  //this is a vector stack
	v->push(8);

	int x = 0;

	v->pop(x);

	cout << x << endl;
    
    x=0;
    
    Stack<int> *l = make_stack<int>(false); //this is a linked list stack
    l->push(9);
    
    l->pop(x);
    
    cout << x << endl;
    
    delete v;
    delete l;
    
	return 0;
}