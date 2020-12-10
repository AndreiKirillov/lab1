#pragma once
#include<iostream>
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include<vector>
#include<set>
using namespace std;

class Graph
{
public:
    ///////���� ������
    set<int> Pipes_in_Graph;         //и��� �����
    set<int> KS_in_Graph;            //������� �����
    vector<vector<int>> Matrix;      //������� ����������
    ///////������ ������
    void ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks);
    vector<vector<int>> CreateGraph(const vector<Pipe>& p, const vector<KS>& ks);
    void PrintGraph(const vector<vector<int>>& matrix);
};

