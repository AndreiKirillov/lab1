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
    ///////���� ������
    set<int> Pipes_in_Graph;         //и��� �����
    set<int> KS_in_Graph;            //������� �����
    vector<vector<int>> Matrix;      //������� ���������
    bool EmptyGraph;
    ///////������ ������
    void ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks);   //���������� ��
    void CreateGraph(const vector<Pipe>& p, const vector<KS>& ks);    //�������� ������� ���������
    bool CheckLine(int index, string parametr);                    //��������������� �������
    void PrintGraph();     //����� ������� ��������� � �������
    bool CheckCycle();      //�������� �� �����
    void TopologicalSort(); //�������������� ����������
    void MaxFlow(const vector<Pipe>& p, const vector<KS>& ks);   //������� ������� ������������� ������ ����
};

