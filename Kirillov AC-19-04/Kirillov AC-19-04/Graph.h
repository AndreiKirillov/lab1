#pragma once
#include<iostream>
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include<vector>
#include<set>
#include<map>
using namespace std;

class Graph
{
public:
    ///////Поля класса
    set<int> Pipes_in_Graph;         //Рёбра графа
    set<int> KS_in_Graph;            //Вершины графа
    vector<vector<int>> Matrix;      //Матрица инциденций
    ///////Методы класса
    void ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks);
    void CreateGraph(const vector<Pipe>& p, const vector<KS>& ks);
    void PrintGraph();
    //bool CheckCycle();
    void TopologicalSort();
};

