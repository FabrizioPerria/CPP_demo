#include <iostream>

using namespace std;

class Base{
public:
       Base(){}
       virtual void f1() = 0;
       void f2(){ cout << "B2" << endl;}
};

class Derived : public Base {
public:
       Derived() {}
       void f1() { cout << "D1" << endl;}
       void f2() { cout << "D2" << endl;}
};


int main(void)
{
       Derived D;
       Base *b=&D;
       b->f1();                   //polymorphism due to pure virtual method on base class
       b->f2();                   //ven if b is getting the address of a derived class.....it is still a base class so will print B2

       return 0;
}
