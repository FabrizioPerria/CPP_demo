#include <iostream>
#include <list>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "Edge.h"

using namespace std;

const int SIZE_RANDOM_MATRIX = 6;

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
    list<Edge> forest;
    for(int i=0;i<SIZE_MATRIX;i++){
        for(int j=0;j<SIZE_MATRIX;j++){
            if(graph[i][j])
                forest.push_back(*new Edge(i,j,graph[i][j]));
        }
    }
    list<Edge> MST;

    forest.sort();

    vector<int> roots(SIZE_MATRIX,-1);

    for(list<Edge>::iterator it=forest.begin(); it != forest.end(); it++){
        if((roots[it->getSrc()] < 0) || (roots[it->getDst()] < 0)){
            MST.push_back(*it);
            if(roots[it->getSrc()] < 0){
                roots[it->getSrc()] = it->getSrc();
            }

            roots[it->getDst()] = roots[it->getSrc()];

        } else if((roots[it->getSrc()]) != (roots[it->getDst()])){
            MST.push_back(*it);
            int j=roots[it->getDst()];
            for(int i = 0; i < SIZE_MATRIX;i++){
                if(roots[i] == j)
                    roots[i] = roots[it->getSrc()];
            }
        } else continue;
    }

    for(list<Edge>::iterator it=MST.begin(); it != MST.end(); it++){
        cout << *it << endl;
    }

    return 0;
}
