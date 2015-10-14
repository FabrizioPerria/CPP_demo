#include "Node.h"

ostream& operator<<(ostream& out,Node& n)
{
	out << "Node: " << n.ID << " Cost: " << n.cost << " From: " << n.fatherID << " ";
	return out;
}

Node::Node(int ID,int cost):ID(ID),cost(cost),fatherID(-1){}

Node::Node(const Node& n):ID(n.ID),cost(n.cost),fatherID(n.fatherID){}

Node::~Node(){}

int Node::getCost()
{
	return this->cost;
}

void Node::setCost(int value)
{
	this->cost = value;
}

int Node::getID()
{
	return this->ID;
}

void Node::setID(int value)
{
	this->ID = value;
}

int Node::getFather()
{
	return this->fatherID;
}

void Node::setFather(int value)
{
	this->fatherID = value;
}