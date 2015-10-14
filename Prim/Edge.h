#include <iostream>

using namespace std;

class Edge{
public:
    Edge();
    Edge(int src,int dst,int cost=-1);
    ~Edge();

    int getSrc();
    int getDst();
    int getCost();
    friend ostream& operator<<(ostream& out, const Edge& e);
    friend bool operator<(Edge& a,Edge& b);

private:
    int src,dst,cost;
};
