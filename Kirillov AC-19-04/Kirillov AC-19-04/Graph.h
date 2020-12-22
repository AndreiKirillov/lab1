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
    ///////Ïîëÿ êëàññà
    unordered_set<int> Pipes_in_Graph;         //Ð¸áðà ãðàôà
    unordered_set<int> KS_in_Graph;            //Âåðøèíû ãðàôà
    vector<int> ReNumbered_ks;         //õðàíèì ïîðÿäîê ïîïàäàíèÿ êñ â ñåòü(îò 0)
    set<int> KS_lines;         //Çäåñü êñ, êîòîðûå ìîãóò áûòü íà÷àëîì
    set<int> KS_columns;       //êîíöîì
    vector<vector<int>> Matrix;      //Ìàòðèöà ñìåæíîñòè
    //vector<vector<int>> WeightMatrix;
    struct edge {        //ñòðóêòóðà ðåáåð ãðàôà, õðàíèò óïîðÿäî÷åííûé íîìåð input, output è length òðóáû â ãðàôå
        int a,b, cost;
    };
    vector<edge> All_edges;     //âåêòîð âñåõ ð¸áåð ãðàôà
    bool EmptyGraph;          //true êîãäà ïóñòîé ãðàô
    ///////Ìåòîäû êëàññà
    void ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks);   //Ñîåäèíåíèå êñ

    void CreateGraph();    //Ñîçäàíèå ìàòðèöû ñìåæíîñòè

    //bool CheckLine(int index, string parametr);                    //Âñïîìîãàòåëüíàÿ ôóíêöèÿ
    void PrintGraph();     //Âûâîä ñïèñêîâ ñìåæíîñòè â êîíñîëü
    bool CheckCycle();      //Ïðîâåðêà íà öèêëû
    void TopologicalSort(); //Òîïîëîãè÷åñêàÿ ñîðòèðîâêà

    void MaxFlow();   //Ôóíêöèÿ ðàñ÷¸òà ìàêñèìàëüíîãî ïîòîêà ñåòè

    int ShortestWay(int v, int end);
    int ConvertKS(int ks_id); //Âñïîìîãàòåëüíàÿ ôóíêöèÿ, êîíâåðòèðóåò id êñ â å¸ ïîðÿäêîâûé íîìåð
    int UserChooseKS_inGraph(set<int>& set_ks);  //Âçàèìîäåéñòâèå ñ ïîëüçîâàòåëåì; îí âûáèðàåò íà÷àëüíóþ è êîíå÷íóþ âåðøèíû
    friend ofstream& operator <<(ofstream& outf, const Graph& g);
};

