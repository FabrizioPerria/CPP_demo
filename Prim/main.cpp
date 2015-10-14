#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Edge.h"

using namespace std;

const int SIZE_RANDOM_MATRIX = 5;

int main(int argc, char **argv)
{
/************************************
    GRAPH CREATION
**************************************/
    int **graph;
    int SIZE_MATRIX=0;
    if(argc > 1){
        ifstream file(argv[1]);
        if(!file){
            cout << "File Not Found" << endl;
            return -1;
        }
        file >> SIZE_MATRIX;

        graph = new int*[SIZE_MATRIX];

        for(int i = 0; i< SIZE_MATRIX; i++){
            graph[i] = new int[SIZE_MATRIX];
        }

        for(int i = 0; i< SIZE_MATRIX; i++){
            for(int j = 0; j < SIZE_MATRIX; j++){
                file >> graph[i][j];
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        SIZE_MATRIX = SIZE_RANDOM_MATRIX;
        srand(time(0));

        graph = new int*[SIZE_MATRIX];
        for(int i = 0; i< SIZE_MATRIX; i++){
            graph[i] = new int[SIZE_MATRIX];
        }

        for(int i = 0; i< SIZE_MATRIX; i++){
            for(int j = 0; j <SIZE_MATRIX; j++){
                if (i == j) graph[i][j] = 0;
                else graph[i][j] = (rand()%10);
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
    }

    list<Edge> MST;

    vector<bool> flags(SIZE_MATRIX,false);
    flags[0]=true;
    list<Edge> availableEdges;

    int cnt=1;
    int i=0;
    while(cnt != SIZE_MATRIX && i >= 0){
        for(int j=0;j<SIZE_MATRIX;j++){
            if(graph[i][j])
                availableEdges.push_back(*new Edge(i,j,graph[i][j]));
        }
        availableEdges.sort();
        for(list<Edge>::iterator it=availableEdges.begin(); it != availableEdges.end(); it++){
            cout << *it << endl;
        }
        getchar();
        i=-1;
        for(list<Edge>::iterator it=availableEdges.begin();it!=availableEdges.end();it++){
            if(!flags[it->getDst()]){
                flags[it->getDst()] = true;
                cnt++;
                i=it->getDst();
                MST.push_back(*it);
                availableEdges.erase(it);
                break;
            }
        }
    }
    if(i < 0)
        cout << "Impossible to build the minimum spanning tree of this graph!" << endl;
    else {
        cout << endl;
        for(list<Edge>::iterator it=MST.begin(); it != MST.end(); it++){
            cout << *it << endl;
        }
    }

    return 0;
}
