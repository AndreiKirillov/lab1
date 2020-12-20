#pragma once
#include<iostream>
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include<string>
#include<vector>
#include<unordered_set>
#include<map>
using namespace std;

class Graph
{
public:
    ///////Поля класса
    unordered_set<int> Pipes_in_Graph;         //Рёбра графа
    unordered_set<int> KS_in_Graph;            //Вершины графа
    vector<int> ReNumbered_ks;         //храним порядок попадания кс в сеть(от 0)
    vector<vector<int>> Matrix;      //Матрица смежности
    vector<vector<int>> WeightMatrix;
    struct edge {        //структура ребер графа, хранит упорядоченный номер input, output и length трубы в графе
        int a,b, cost;
    };
    vector<edge> All_edges;     //вектор всех рёбер графа
    bool EmptyGraph;
    ///////Методы класса
    void ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks);   //Соединение кс
    void CreateGraph(const vector<Pipe>& p, const vector<KS>& ks);    //Создание матрицы смежности
    bool CheckLine(int index, string parametr);                    //Вспомогательная функция
    void PrintGraph();     //Вывод списков смежности в консоль
    bool CheckCycle();      //Проверка на циклы
    void TopologicalSort(); //Топологическая сортировка
    void MaxFlow(const vector<Pipe>& p, const vector<KS>& ks);   //Функция расчёта максимального потока сети
    int ShortestWay(int v, int end, const vector<Pipe>& p, const vector<KS>& ks);
};

