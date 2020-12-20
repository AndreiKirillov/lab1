#pragma once
#include<iostream>
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include<string>
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
    vector<vector<int>> Matrix;      //Матрица смежности
    bool EmptyGraph;
    ///////Методы класса
    void ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks);   //Соединение кс
    void CreateGraph(const vector<Pipe>& p, const vector<KS>& ks);    //Создание матрицы смежности
    bool CheckLine(int index, string parametr);                    //Вспомогательная функция
    void PrintGraph();     //Вывод списков смежности в консоль
    bool CheckCycle();      //Проверка на циклы
    void TopologicalSort(); //Топологическая сортировка
    void MaxFlow(const vector<Pipe>& p, const vector<KS>& ks);   //Функция расчёта максимального потока сети
};

