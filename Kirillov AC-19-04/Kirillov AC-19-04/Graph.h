#pragma once
#include<iostream>
#include<fstream>
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include<string>
#include<vector>
#include<unordered_set>
#include<set>
#include<map>
using namespace std;

class Graph
{
public:
    ///////���� ������
    unordered_set<int> Pipes_in_Graph;         //и��� �����
    unordered_set<int> KS_in_Graph;            //������� �����
    vector<int> ReNumbered_ks;         //������ ������� ��������� �� � ����(�� 0)
    set<int> KS_lines;         //����� ��, ������� ����� ���� �������
    set<int> KS_columns;       //������
    vector<vector<int>> Matrix;      //������� ���������
    vector<vector<int>> WeightMatrix;
    struct edge {        //��������� ����� �����, ������ ������������� ����� input, output � length ����� � �����
        int a,b, cost;
    };
    vector<edge> All_edges;     //������ ���� ���� �����
    bool EmptyGraph;
    ///////������ ������
    void ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks);   //���������� ��
    void CreateGraph(const vector<Pipe>& p, const vector<KS>& ks);    //�������� ������� ���������
    bool CheckLine(int index, string parametr);                    //��������������� �������
    void PrintGraph();     //����� ������� ��������� � �������
    bool CheckCycle();      //�������� �� �����
    void TopologicalSort(); //�������������� ����������
    void MaxFlow(const vector<Pipe>& p, const vector<KS>& ks);   //������� ������� ������������� ������ ����
    int ShortestWay(int v, int end);
    int ConvertKS(int ks_id); //��������������� �������, ������������ id �� � � ���������� �����
    int UserChooseKS_inGraph(set<int>& set_ks);  //�������������� � �������������; �� �������� ��������� � �������� �������
    friend ofstream& operator <<(ofstream& outf, const Graph& g);
};

