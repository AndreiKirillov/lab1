#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Pipe.h"
#include "KS.h"
#include "Source.h"
#include "Graph.h"
using namespace std;

double GetNumber(double min, double max)          //������� ��� �������� ������� ����� � ����������
{
	double a;
	while ((cin >> a).fail() || a < min || a > max)
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "������� ���������� �����!" << endl;
	}
	return a;
}

void NewPipe(vector<Pipe>& p)          //������� �������� ����� �����
{
	Pipe p1;
	cout << "������� ����� �����:";
	p1.length=GetNumber(1, 10000000);
	cout << "������� ������� �����:";
	p1.diametr=GetNumber(1, 10000000);
	p.push_back(p1);               //��������� � ����� ������� ����
	p[p.size() - 1].id=p.size();
}

void NewKS(vector<KS>& ks)                  //������� �������� ����� ������������� �������
{
	KS ks1;
	ks1.SetName();
	cout << "������� ����� ���-�� �����:";
	ks1.SetNumber_ceh(GetNumber(1.0, 100000.0));
	cout << "������� ���-�� ����� � ������:";
	ks1.SetNumber_ceh_inWork(GetNumber(0.0, 100000.0));
	ks1.efficiency= (ks1.number_ceh_inWork / ks1.number_ceh) * 100;
	ks.push_back(ks1);                       //��������� ���������� � ����� �������
	ks[ks.size() - 1].id=ks.size();
}    

void PrintData(const vector<Pipe>& p,const vector<KS>& ks)   //������� ��� ������ ������ � �������
{
	int i;
	cout << "������ ����:" << endl;
	if (p.size() == 0)       //���� ������ ���� ����, ������ �� �������
	{
		cout << "������ ���� ����" << endl << " " << endl;
	}
	else
	{
		for (i = 0; i < p.size(); i++)
		{
			cout << p[i] << endl;      //���������� ���������� ��������� ������
		}
	}
	cout << "������ ������������� �������:" << endl;
	if (ks.size() == 0)
	{
		cout << "������ ������������� ������� ����" << endl << " " << endl;
	}
	else
	{
		for (i = 0; i < ks.size(); i++)
		{
			cout << ks[i] << endl;
		}
	}
}

vector<int> FindPipe(const vector<Pipe>& p, int MaxPossibleValue);   //���������� ����� ������������ �������

void RedactPipe(vector<Pipe>& p)            //������� ��� �������������� �����
{
	if (p.size() == 0)
	{
		cout << "��� ��������� ���� ��� ��������������" << endl;
	}
	else
	{
	    vector<int> pipe_indexes = FindPipe(p, p.size());             //������ ������ ��������� ����
		for (int i = 0; i < pipe_indexes.size(); i++)
		{
			p[pipe_indexes[i]].ChangeStatus();
		}
	}
}

void RedactKS(vector<KS>& ks)      //������� ��� �������������� ��
{
	if (ks.size() == 0)
	{
		cout << "��� ��������� ������������� ������� ��� ��������������" << endl;
	}
	else
	{
		cout << "������� ID ������������� �������, ������� ������ �������������(�������� " << 1 << "-" << ks.size() << ")" << endl;
		int id = GetNumber(1, ks.size())-1;
		cout << "��� ������ �� ������ �������������?" << endl;
		int WhatToRedact;  //����������, � �� ��������� �����, ���������� �� ��� ����� ������������� ������������
		do
		{
			cout << "1-������������� ���" << endl << "2-������������� ���-�� �����" << endl 
				<< "3-������������� ���������� ���������� �����" << endl
				<< "0-��������� ��������������" << endl;   //���� ��������������
			WhatToRedact=GetNumber(0,3);
			switch (WhatToRedact)   //����������� ������ ��������, � ����������� �� ����������
			{
			case 1:
				ks[id].SetName();
				break;
			case 2:
				cout << "������� ����� ���-�� ����� ��:" << endl;
				ks[id].SetNumber_ceh(GetNumber(ks[id].number_ceh_inWork, 100000));
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;;
				break;
			case 3:
				cout << "������� ����� ���-�� ���������� ����� ��:" << endl;
				ks[id].SetNumber_ceh_inWork(GetNumber(1.0, 100000.0));
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;;
				break;
			case 0:
				break;
			}
		} while (WhatToRedact != 0);   //������� �� �����, ����� ������������ ����� 0
	}
}

vector<int> FindPipe(const vector<Pipe>& p, int MaxPossibleValue)        //������� ���������� ����
{
	vector<int> res;
	if (MaxPossibleValue > 1)
	{
		cout << "1 - ����� � �������" << endl <<
			"2 - ����� ��� �������" << endl <<
			"3 - ������� ���������� �����" << endl;
		int what_to_find = GetNumber(1, 3);
		int i;
		if (what_to_find == 1)
		{
			for (i = 0; i < p.size(); i++)
			{
				if (p[i].remont)      //����� � �������
					res.push_back(i);
			}
		}
		if (what_to_find == 2)
		{
			for (i = 0; i < p.size(); i++)
			{
				if (!p[i].remont)        //����� ��� �������
					res.push_back(i);
			}
		}
		if (what_to_find == 3)
		{
			if (p.size() != 0)
			{
				cout << "������� ID ����, ������� ������ ����� (�������� " << 1 << "-" << p.size() << ")" << endl <<
					"����� ���������, ������� ����" << endl;
				int id;
				do
				{                                                 //���� ����� �� ������� ������������
					id = GetNumber(0, p.size());
					if (id != 0)
						res.push_back(id - 1);
				} while (id != 0);
			}
		}
		if (res.size() == 0)
			cout << "���� �� ������ ���������� �� �������!" << endl;
		return res;
	}
	else
	{
		if (p.size() > 0)
		{
			cout << "����� ������� ������ ���� �����!" << endl;
			cout << "������� ID �����, ������� ������ ������� (�������� " << 1 << "-" << p.size() << ")" << endl;
			int pipe_id = GetNumber(1, p.size());
			res.push_back(pipe_id-1);
			return res;
		}
		else
		{
			res.push_back(-1);
			cout << "���� �� ����������!" << endl;
			return res;
		}
	}
	
}

template<typename T>                                  //������
using Filter = bool(*)(const KS&, T parametr);        //��������� �� ������� 

bool CheckByID(const KS& ks, int parametr)
{
	return ks.id == parametr;
}

bool CheckByName(const KS& ks, string parametr)        //������� ��� ������ �� �����
{
	return ks.name == parametr;
}

bool CheckByProcent(const KS& ks, double parametr)       //������� ��� ������ �� ��������������� �����
{
	return ks.efficiency >= parametr;
}

template<typename T>
vector<int> FindKS(const vector<KS>& ks, Filter<T> f, T parametr)         //������� ���������� ��
{
	vector<int> res;                         //������ ��� �������� ��������
	int i;
	for (i = 0; i < ks.size(); i++)
	{
		if (f(ks[i], parametr))            //��������� ���������� � ������� ���������
			res.push_back(i);
	}		
	return res;
}

vector<int> UserChooseKS(const vector<KS>& ks, int MaxPossibleValue)
{
	vector<int> ks_indexes;                                              //������, �������� ������� ��������� ��
	cout << "1-������ �� �� ID" << endl << "2-������ �� �� ��������" << endl << "3-������ �� �� �������� ��������������� �����" << endl;
    int what_to_find = GetNumber(1, 3);
	if (what_to_find == 1)
	{
		if (ks.size() != 0)
		{
			cout << "������� ID ��, ������� ������ ����� (�������� " << 1 << "-" << ks.size() << ")" << endl <<
				"����� ���������, ������� ����" << endl;
			int id;
			do
			{                                                 //���� �� �� ������� ������������
				id = GetNumber(0, ks.size());
				if (id != 0)
					ks_indexes.push_back(id - 1);
			} while (id != 0 && ks_indexes.size()<MaxPossibleValue);
		}
	}else
	if (what_to_find == 2)
	{
		cout << "������� ��� ��: ";
		string find_name;
		cin >> find_name;
		ks_indexes = FindKS<string>(ks, CheckByName, find_name);
	}else
	if (what_to_find == 3 && MaxPossibleValue>1)
	{
		double procent;
		cout << "������� �������� ������� ��������������� �����: ";
		procent = GetNumber(0.0, 100.0);
		ks_indexes = FindKS(ks, CheckByProcent, procent);
	}else
	{
		cout << "������ ������ �� �������� ������������� �����!" << endl;
	}
	if (MaxPossibleValue > 1)
		return ks_indexes;
	else
	{
		if(ks_indexes.size()==0)
		ks_indexes.push_back(-1);
		return ks_indexes;
	}
}

void DeletePipes(vector<Pipe>& p, Graph& g)        //�������� ����
{
	vector<int> pipe_indexes = FindPipe(p,p.size());
	for (int i = 0; i < p.size(); i++)
	{
		for (int j = 0; j < pipe_indexes.size(); j++)
		{
			if (p[i].id == pipe_indexes[j]+1)
			{
				
				if (g.Pipes_in_Graph.find(pipe_indexes[j] + 1) != g.Pipes_in_Graph.end())
					g.Pipes_in_Graph.erase(pipe_indexes[j] + 1);
				int value = 0;
				for (int k = 0; k < g.All_edges.size(); k++)
					if (g.All_edges[k].a == pipe_indexes[j] + 1 || g.All_edges[k].b == pipe_indexes[j] + 1)
						value++;
				if(value>0 && value<2)

				p.erase(p.begin() + i);
			}
		}
	}
	for (int i = 0; i < p.size(); i++)
	{
		p[i].id = i + 1;
	}
}

void DeleteKS(vector<KS>& ks, vector<Pipe>& p, Graph& g)      //�������� ��
{
	vector<int> ks_indexes = UserChooseKS(ks, ks.size());
	for (int i = 0; i < ks.size(); i++)
	{
		for (int j = 0; j < ks_indexes.size(); j++)
		{
			if (ks[i].id == ks_indexes[j] + 1)           
			{
				for (auto& pipe : p)              //���� �� ������������� � ����, �� ���� ������� ����� ���� � ���
					if (pipe.input == ks[i].id || pipe.output == ks[i].id)
					{
						pipe.input = 0;
						pipe.output = 0;
						g.Pipes_in_Graph.erase(pipe.id);
					}
				if (g.KS_in_Graph.find(ks_indexes[j]) != g.KS_in_Graph.end())
					g.KS_in_Graph.erase(ks_indexes[j] + 1);
				if (g.KS_lines.find(ks_indexes[j]) != g.KS_lines.end())
					g.KS_lines.erase(ks_indexes[j] + 1);
				if (g.KS_columns.find(ks_indexes[j]) != g.KS_columns.end())
					g.KS_columns.erase(ks_indexes[j] + 1);
				for (int i = 0; i < g.ReNumbered_ks.size(); i++)
					if (g.ReNumbered_ks[i] == ks_indexes[j] + 1)
						g.ReNumbered_ks.erase(g.ReNumbered_ks.begin() + i);
				ks.erase(ks.begin() + i);
			}
		}
	}
	for (int i = 0; i < ks.size(); i++)
	{
		ks[i].id = i + 1;
	}
}

void SaveData(const vector<Pipe>& p,const vector<KS>& ks, const Graph& g)       //�������� ������� ����������
{
	cout << "������� �������� ����� ��� ����������" << endl;
	string filename;
	cin >> filename;
	filename += ".txt";
	ofstream outf;
	int i;
	outf.open(filename);
	if (p.size() == 0 && ks.size() == 0)   //����� ������� ������ ���� � �� �����, ���������� �� ��������� 
	{
		cout << "��� ������ ��� ����������!" << endl;
	}
	else if (outf.is_open())
	{
		outf << p.size() << endl;     //� ������ ������ ������� ���-�� ����
		outf << ks.size() << endl;    //�� ������ ���-�� �� 
		outf << g.Pipes_in_Graph.size() << endl;  //�������� �������� ��������� ����
		outf << g.KS_in_Graph.size() << endl;
		outf << g.ReNumbered_ks.size() << endl;
		outf << g.KS_lines.size() << endl;
		outf << g.KS_columns.size() << endl;
		outf << g.All_edges.size() << endl;
		for (i = 0; i < p.size(); i++)           //������� ��������� ������ ����� �� ������ 
		{
			outf << p[i];
		}
		for (i = 0; i < ks.size(); i++)           //������� ��������� ������ �� �� ������ 
		{
			outf << ks[i];
		}
		outf << g << endl;
		cout << "������ ������� ���������!" << endl;
	};
	outf.close();
}

void DownloadSaves(vector<Pipe>& p, vector<KS>& ks, Graph& g)         //�������� ������� ��������   
{
	cout << "������� �������� ����� ��� ��������" << endl;
	string filename;
	cin >> filename;
	filename += ".txt";
	ifstream inf;
	int i=0;
	int SizePipes, SizeKS, SizePipes_in_Graph, SizeKS_in_Graph, SizeRenumberedKS, SizeKS_lines, SizeKS_columns, SizeAll_edges;
	inf.open(filename);
	if (inf.is_open())
	{
		inf >> SizePipes;                       //��������� ���������� ���� � ����������
		inf >> SizeKS;                         //������ ���-�� ��
		inf >> SizePipes_in_Graph;
		inf >> SizeKS_in_Graph;
		inf >> SizeRenumberedKS;
		inf >> SizeKS_lines;
		inf >> SizeKS_columns;
		inf >> SizeAll_edges;
		if (SizePipes == 0 && SizeKS == 0)    //���� �������� ������� �� ��������� ������ 
		{
			cout << "�� ������� ��������� ������, ���� ����!" << endl;
		}
		else
		{
			int data;
			p.resize(SizePipes);
			ks.resize(SizeKS);
			g.ReNumbered_ks.resize(SizeRenumberedKS);
			g.All_edges.resize(SizeAll_edges);
			for (i = 0; i < p.size(); i++)   //�� ������� ���������� ������ � ������ ����
				inf >> p[i];
			for (i = 0; i < ks.size(); i++)    //�� ������� ���������� ������ � ������ ��
				inf >> ks[i];
			for (i = 0; i < SizePipes_in_Graph;i++)
			{
				inf >> data;
				g.Pipes_in_Graph.insert(data);
			}
			for (i = 0; i < SizeKS_in_Graph; i++)
			{
				inf >> data;
				g.KS_in_Graph.insert(data);
			}
			for (i = 0; i < g.ReNumbered_ks.size(); i++)
				inf >> g.ReNumbered_ks[i];
			for (i = 0; i < SizeKS_lines; i++)
			{
				inf >> data;
				g.KS_lines.insert(data);
			}
			for (i = 0; i < SizeKS_columns; i++)
			{
				inf >> data;
				g.KS_columns.insert(data);
			}
			for (i = 0; i < g.ReNumbered_ks.size(); i++)
			{
				inf >> g.All_edges[i].a;
				inf >> g.All_edges[i].b;
				inf >> g.All_edges[i].cost;
			}
			cout << "�������� ������ �������" << endl;
		}
	}
	else
		cout << "�� ������� ���������� ��������, ������� ���������� ��� �����!" << endl;
	inf.close();
}

void Menu()          //������� ������ ����, ������� ������ ��������� �������� ������������
{
	cout << "���� ���������" << endl <<
		"1-�������� �����" << endl <<
		"2-�������� ������������� �������" << endl <<
		"3-��������� ������������� �������" << endl <<
		"4-�������� ���� ��������" << endl <<
		//"5-������������� �����" << endl <<
		//"6-������������� ������������� �������" << endl <<
		//"7-����� ���� �� �������� '� �������'" << endl <<
		//"8-����� ������������� �������" << endl <<
		"9-������� �������" << endl <<
		"10-�������� ���������������� ����" << endl <<
		"11-�������������� ����������" << endl <<
		"12-����� ���������� ����" << endl <<
		"13-������ ������������� ������ ����" << endl <<
		"14-��������� � ����" << endl <<
		"15-��������� �� �����" << endl <<
		"16-������� ����" << endl <<
		"0-����� �� ���������" << endl;
}

int MakeStep()      // �������, ������������ �����-��������, ������� ����� ��������� ������������
{
	cout << "����� �������� �� ������ �������?" << endl;
	int a = GetNumber(0, 16);
	return a;
}

int main()
{
	setlocale(LC_ALL, "Russian");          //����������� �������� �����
	vector <Pipe> pipes;                       //������ ��� �������� ����
	vector <KS> ks;                            //������ ��� �������� ��
	Graph GasNetwork;
	Menu();                                  //���������� ����            
	while (1)                   
	{
		int operation = MakeStep();          //����������� �������� ������������
		switch (operation)                   //���� ��� ��������� ��������, ��������� �������������
		{
		case 1:
			NewPipe(pipes);  //������� ����� �����
			break;
		case 2:
			NewKS(ks);        //������� ����� ��
			break;
		case 3:
			GasNetwork.ConnectKSbyPipe(pipes, ks);
			break;
		case 4:                                  //����� ������ �������� � �������
			PrintData(pipes, ks);
			break;
		case 5:                                   //����������� ������ "� �������" ��� �����
			RedactPipe(pipes);
			break;
		case 6:                //��������������� ��
			RedactKS(ks);
			break;
		case 7:
		    {
			cout << "����� ���� " << endl;
				vector<int> pipe_indexes = FindPipe(pipes,pipes.size());       //������, �������� ������� ��������� ����
				if (pipe_indexes.size() > 0)                      
				{
					int i;
					for (i = 0; i < pipe_indexes.size(); i++)
						cout << pipes[pipe_indexes[i]];            //������� ��������� �����
				}
		    }
			break;
		case 8:
		{
			vector<int> ks_indexes = UserChooseKS(ks,ks.size());                                            //������, �������� ������� ��������� ��
			if (ks_indexes.size() > 0)
			{
				cout << "��������� ������������� �������:" << endl;
				int i; 
				for (i = 0; i < ks_indexes.size(); i++)
					cout << ks[ks_indexes[i]];
			}
			else
				cout << "������������� ������� � ������� ����������� �� �������!" << endl;
		}
		break;
		case 9:
		{
			cout << "��� �� ������ �������?" << endl << "1-�����" << endl << "2-��" << endl;
			int WhatToDelete = GetNumber(1, 2);
			if (WhatToDelete == 1)
			{
				DeletePipes(pipes,GasNetwork);
			}
			else
			{
				DeleteKS(ks, pipes, GasNetwork);
			}
		}
		break;
		case 10:
		{
			GasNetwork.CreateGraph(pipes,ks);
			GasNetwork.PrintGraph();
		}
		break;
		case 11:
		{
			GasNetwork.CreateGraph(pipes, ks);
			GasNetwork.TopologicalSort();
		}
		break;
		case 12:
		{
			GasNetwork.CreateGraph(pipes, ks);
			if (GasNetwork.EmptyGraph)
				cout << "������! ����������� ���������������� ����!" << endl;
			else
			{
				GasNetwork.PrintGraph();             //���������� ������������ ����
				cout << "�������� ��������� ��, ��������: ";
				int beginning = GasNetwork.UserChooseKS_inGraph(GasNetwork.KS_lines);
				cout << "�������� �������� ��, ��������: ";
				int end = GasNetwork.UserChooseKS_inGraph(GasNetwork.KS_columns);
				if (beginning != end)
				{
					int Length = GasNetwork.ShortestWay(beginning, end);
					cout << "���������� ���� ����� ��������� ����� " << endl;
					cout << Length << endl;
				}
				else
					cout << "��������� � �������� ������� ���������, ���������� �����!" << endl;
			}
		}
		break;
		case 13:
		{
			GasNetwork.CreateGraph(pipes, ks);
			if (GasNetwork.EmptyGraph)
				cout << "������! ����������� ���������������� ����!" << endl;
			else
			{
				cout << "�������� ��������� ��, ��������: ";
				int beginning = GasNetwork.UserChooseKS_inGraph(GasNetwork.KS_lines);
				cout << "�������� �������� ��, ��������: ";
				int end = GasNetwork.UserChooseKS_inGraph(GasNetwork.KS_columns);
				if (beginning != end)
				{
					GasNetwork.MaxFlow(beginning, end);
				}
			}
		}
		break;
		case 14:
			SaveData(pipes, ks, GasNetwork);      //���������� ������ � ���� �� �������� ���� � ��
			break;
		case 15:
			DownloadSaves(pipes, ks, GasNetwork);    //�������� ������ �� �����
			break;
		case 16:                          //����� ����
			Menu();
			break;
		case 0:
			return 0;
			break;
	    }
    }
}


