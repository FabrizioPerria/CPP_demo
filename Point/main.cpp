#include <iostream>
#include "Point.h"

using namespace std;

int main(void)
{
	Point a;				//default constructor
	Point b(1);				//constructor with 1 default element(y)
	Point c(8.5,1);			//constructor

	cout <<"Print: "<<endl; //separate the copy constructor calls for the cout
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;			//after each cout the copy is destroyed

	a+=b;					//+= operator
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;

	a-=b;					//-=operator
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;

	b*=25;					//*= operator
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;

	b/=50;					///=operator
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;

	a=b;					//assignment operator
	a.setX(100);			//proof that is deep copy
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;

	b = b*300;				//= and * operator
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;

	a = a/10;				//= and / operator
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;

	a=a+c;					//= and + operator
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;
	
	a=a-b;					//= and - operator
	cout << "A: "<< a << endl <<"B: "<< b << endl <<"C: "<< c << endl;

	system("pause");
	return 0;
}