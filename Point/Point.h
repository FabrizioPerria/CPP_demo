#include <iostream>

using namespace std;

class Point{
public:
	Point(double x=0,double y=0);					//constructor and default constructor
	~Point();										//destructor

	Point(const Point& p);							//copy constructor

	void setX(double value);
	double getX();

	void setY(double value);
	double getY();

	friend ostream& operator<<(ostream& out,const Point p);
	friend Point& operator+(Point& a,const Point& b);
	friend Point& operator-(Point& a,const Point& b);
	friend Point& operator*(Point& a,const double scalar);
	friend Point& operator/(Point& a,const double scalar);
	Point& operator=(const Point& p);				//assignment operator
	Point& operator+=(const Point& p);
	Point& operator-=(const Point& p);
	Point& operator*=(const double scalar);
	Point& operator/=(const double scalar);

private:
	double x,y;
};