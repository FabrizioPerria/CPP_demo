#include <iostream>

using namespace std;

class Node{
public:
	Node(int ID=0,int cost=0);			//constructor and default constructor
	~Node();								//destructor
	Node(const Node& n);					//copy constructor
	
	friend ostream& operator<<(ostream& out,Node& n);
	int getCost();
	void setCost(int value);
	int getID();
	void setID(int value);
	int getFather();
	void setFather(int value);
private:
	int cost;
	int ID;
	int fatherID;
};
