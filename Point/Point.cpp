#include <iostream>
#include "Point.h"

using namespace std;

Point::Point(double x,double y):x(x),y(y)
{
	cout << "Constructor" << endl;
}

Point::~Point()
{
	cout << "Destructor" << endl;
}

Point::Point(const Point& p):x(p.x),y(p.y)
{
	cout << "Copy constructor" << endl;
}

ostream& operator<<(ostream& out,const Point p)
{
	out << "(" << p.x << ","<<p.y<<")";
	return out;
}

Point& operator+(Point& a,const Point& b)
{
	cout << "Operator +"<<endl;
	a.x += b.x;
	a.y += b.y;
	return a;
}

Point& operator-(Point& a,const Point& b)
{
	cout << "Operator -"<<endl;
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

Point& operator*(Point& a,const double scalar)
{
	cout << "Operator *"<<endl;
	a.x *= scalar;
	a.y *= scalar;
	return a;
}

Point& operator/(Point& a,const double scalar)
{
	cout << "Operator /"<<endl;
	if(scalar == 0)
		return a;				//should raise an exception
	a.x /= scalar;
	a.y /= scalar;
	return a;
}

Point& Point::operator=(const Point& p)
{
	cout << "Operator ="<<endl;
	this->x=p.x;
	this->y=p.y;
	return *this;
}

Point& Point::operator+=(const Point& p)
{
	cout << "Operator +="<<endl;
	this->x+=p.x;
	this->y+=p.y;
	return *this;
}

Point& Point::operator-=(const Point& p)
{
	cout << "Operator -="<<endl;
	this->x-=p.x;
	this->y-=p.y;
	return *this;
}

Point& Point::operator*=(const double scalar)
{
	cout << "Operator *="<<endl;
	this->x*=scalar;
	this->y*=scalar;
	return *this;
}

Point& Point::operator/=(const double scalar)
{
	cout << "Operator /="<<endl;
	if(scalar == 0)
		return *this;		//should raise an exception
	this->x/=scalar;
	this->y/=scalar;
	return *this;
}

void Point::setX(double value)
{
	this->x = value;
}

double Point::getX()
{
	return this->x;
}

void Point::setY(double value)
{
	this->y = value;
}

double Point::getY()
{
	return this->y;
}