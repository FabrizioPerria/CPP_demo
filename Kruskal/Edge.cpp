#include <iostream>
#include "Edge.h"

using namespace std;

Edge::Edge(int src,int dst,int cost):src(src),dst(dst),cost(cost){}

Edge::Edge(){}

Edge::~Edge(){}

int Edge::getSrc()
{
    return this->src;
}

int Edge::getDst()
{
    return this->dst;
}

int Edge::getCost()
{
    return this->cost;
}

ostream& operator<<(ostream& out, const Edge& e)
{
    out << e.src << " -> " << e.dst << "\t" << e.cost ;
    return out;
}

bool operator<(Edge& a,Edge& b)
{
    return a.cost < b.cost;
}
