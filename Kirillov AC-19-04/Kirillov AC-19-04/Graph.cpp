#include "Graph.h"
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include<vector>
#include<set>
#include<queue>

void Graph::ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks)             //������� ���������� ����� ����� ��
{
	if (p.size() == 0 || ks.size() < 2 || (p.size() == 0 && ks.size() < 2))    //��������� ���������� �� ��������
	{
		cout << "���������� ��������� ��, ��� ��� ������������ ��������" << endl;
	}
	else
	{
		bool PotentialError = false;
		cout << "�������� ��������� ������������� �������:" << endl;            // ������������ �������� ������ �������
		vector<int> begin = UserChooseKS(ks, 1);
		int a = begin[0];
		cout << "�������� �������� ������������� �������:" << endl;            
		vector<int> end = UserChooseKS(ks, 1);
		int b = end[0];                                                             // �, b, pipe - ������
		cout << "�������� ����� ��� ���������� ������������� �������:" << endl;
		vector<int> v = FindPipe(p, 1);
		int pipe = v[0];   
		if (p[pipe].remont == true || Pipes_in_Graph.find(p[pipe].id) != Pipes_in_Graph.end())
		{
			PotentialError = true;            //����� �� ������ ���� � ������� ��� ��� ���� �������������� � ����
			cout << "������ ������������ ������ �����!" << endl;
		}
		if (a >= 0 && b >= 0 && a != b && pipe >= 0 && !PotentialError)       //���� �� ���������
		{
			edge new_edge;
			p[pipe].input = ks[a].id;       //������ id
			p[pipe].output = ks[b].id;
			Pipes_in_Graph.insert(p[pipe].id); 
			if (KS_in_Graph.find(ks[a].id) != KS_in_Graph.end()) //���� ������ �� ��� ���� � ����
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  //���� ����� ���������� ��� ��
					if (ReNumbered_ks[i] == ks[a].id)
						new_edge.a = i;      //������� ����� ������ ��� ��//������ � ���� ���������� �����
			}
			else
			{
				KS_in_Graph.insert(ks[a].id);           //��������� ��������� ������� � ������ ������ ������
				ReNumbered_ks.push_back(ks[a].id);      //������ ����� �������� � ������� ����� ���������� �������
				new_edge.a = ReNumbered_ks.size() - 1;   
			}
			//���� ����� ��� �������� ��
			if (KS_in_Graph.find(ks[b].id) != KS_in_Graph.end()) 
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  
					if (ReNumbered_ks[i] == ks[b].id)
						new_edge.b = i;  
			}
			else
			{
				KS_in_Graph.insert(ks[b].id);           
				ReNumbered_ks.push_back(ks[b].id);
				new_edge.b = ReNumbered_ks.size() - 1;
			}
			new_edge.cost = p[pipe].length;
			All_edges.push_back(new_edge);
		}
		else
		{
			cout << "������! ���������� ������!" << endl;
			if (a == b)
				cout << "���������� ��������� ������ ������������� �������!" << endl;
		}
	}
}

void Graph::CreateGraph()   //������� �������� ������� ���������
{//������������
	if (Pipes_in_Graph.size() == 0)
		EmptyGraph = true;//����������, ��� ���� ������
	else
	{
		vector<vector<int>> matrix(KS_in_Graph.size(), vector<int>(KS_in_Graph.size()));      //
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[i].size(); j++)
				matrix[i][j] = 0;                //
		for (auto ed : All_edges)
			matrix[ed.a][ed.b] = 1;
		Matrix = matrix;
		
		//WeightMatrix = Matrix;
		//for (int pipe : Pipes_in_Graph)    //��������� ������� �����
		//{
		//	WeightMatrix[p[pipe - 1].input][p[pipe - 1].output] = p[pipe - 1].length; //� �������� ���� ����� �����
		//}
	}
}

bool Graph::CheckLine(int index, string parametr)//��������������� ������� �������� ������/������� �� ���� 
{
	if (parametr == "line")//������ ������
	{
		for (int j = 0; j < Matrix.size(); j++)
			if (Matrix[index][j] > 0) //���� ���� ������� �������� �� ���� ���������� true
				return true;
	}else
	if (parametr == "column")//������ �������
	{
		for (int i = 0; i < Matrix.size(); i++)
			if (Matrix[i][index] > 0)
				return true;
	}
	return false;//���� �������� ������ �� �������
}

void Graph::PrintGraph()        //������� ������ ����� � �������
{
	CreateGraph();
	//������� ������ ���������
	if (!EmptyGraph)        //������� ���� ������, ���� ������� �� ������
	{
		cout << "\t���������������� ����\t\n\n" <<
			"������������� ������� <---> ������� � ��� �������" << endl << endl;
		for (int i = 0; i < Matrix.size(); i++)
		{
			bool endline = false;                      //���������� ����� �����, ����� �� ���������� ������
			for (int j = 0; j < Matrix[i].size(); j++)
				if (Matrix[i][j] == 1)
				{
					if (endline == false)
					{
						cout << ReNumbered_ks[i] << "\t-\t" << ReNumbered_ks[j];       //������� id
						endline = true;
					}
					else
						cout << ", " << ReNumbered_ks[j];
				}
			if (endline)
				cout << endl;
		}
		cout << endl;
	}
	else
		cout << "���������������� ���� �� ����������, ��� ��� ��� ������ ����� �������������� ���������" << endl;
}

bool Graph::CheckCycle(vector<int>& visited_ks, int beginning)
{
	visited_ks[beginning] = 1;
	for (int j = 0; j < Matrix[beginning].size(); j++)
		if (Matrix[beginning][j] != 0) {
			if (visited_ks[j] == 0) {
				if (CheckCycle(visited_ks, j)) return true;
			}
			else if (visited_ks[j] == 1)
				return true;
		}
	return false;
}

void Graph::TopologicalSort()       //������� �������������� ����������
{
	CreateGraph();
	bool cycle = false;
	for (int i = 0; i < Matrix.size(); i++)
	{
		vector<int> visited_ks(Matrix.size(), 0);
		if (CheckCycle(visited_ks,0))
		{
			cout << "�������������� ���������� ����������, � ���� ���������� �����!" << endl;
			cycle = true;
			break;
		}
	}
	if (!cycle)
	{
		map<int, int> SortedKS;     //���� - ����� �������, �������� - id ��
		int NumberOfKS = KS_in_Graph.size();           //���������������� �������
		vector<vector<int>> Matrix_Copy = Matrix;      //����� ������� ���������, ����� �������� ������
		unordered_set<int> CopyKS = KS_in_Graph;               //����� ������ �����, ����� ������� ��
		do//���� ���� ���������������� �������
		{
		skip:                     //����� ��� goto
			for (int ks : CopyKS)      //���������� ���������������� �������
			{
				ks = ConvertKS(ks);
				bool VoidLine = true;         //���� ������ ������ � 0
				bool DeletedElement = false;  //���� ������� �������
				for (int j = 0; j < Matrix_Copy[ks].size(); j++)   //��������� ������ �� �����������
				{
					if (Matrix_Copy[ks][j] == 1)
						VoidLine = false;
				}
				if (VoidLine == true)    //���� ������ �� �����
				{
					SortedKS.emplace(NumberOfKS, ReNumbered_ks[ks]); //��������� ������� � ������ ���������������
					NumberOfKS--;                     //���������
					for (int i = 0; i < Matrix_Copy.size(); i++)
						Matrix_Copy[i][ks] = 0;               //�������� �������� �������������� �������
					CopyKS.erase(ReNumbered_ks[ks]);                 //�������� ������� ��� ��������������
					DeletedElement = true;
				}
				if (DeletedElement)       //���� ������� �������, �������� ���� ������
					goto skip;
			}
		} while (NumberOfKS > 0);
		////������� ���������
		cout << "\t��������������� ����������\t\n\n";
		cout << "� �� - id ��" << endl << endl;
		for (auto& n : SortedKS)
		{
			cout << n.first << "\t" << n.second << endl;
		}
	}
}

void Graph::MaxFlow(int u, int v)
{
	if (EmptyGraph)
		cout << "���������� ��������� ������������ �����, ������ ��� � ���� ��� ��������!" << endl;
	else
	{
		vector<vector<int>> matrix(KS_in_Graph.size(), vector<int>(KS_in_Graph.size()));      //������� ������� ������ �� ���-�� �� � ����
		vector<vector<int>> WeightMatrix = matrix;//������� �����
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[i].size(); j++)
			{
				matrix[i][j] = 0;                //�������� ��� ��������
				WeightMatrix[i][j] = 0;
			}
		for (auto ed : All_edges)
		{
			matrix[ConvertKS(ed.a)][ConvertKS(ed.b)] = 1;               //������� ������� �� ���������� ������� �� 0 �� n
			WeightMatrix[ConvertKS(ed.a)][ConvertKS(ed.b)] = ed.cost;   //��������� ������� �����
		}
		//Matrix = matrix;
		bool new_way = true; 
		int Flow;
		vector<edge> Copy_edges = All_edges;
		do
		{

		} while (new_way);
	}
}

int Graph::ShortestWay(int v, int end)//v � end - ���������� ������ ��������� ������� � ��������
{
	const int inf = 100000000;   //�������������
	int NumberOfKS = KS_in_Graph.size();
	int NumberOfPipes = Pipes_in_Graph.size();
	vector<int> Distance(NumberOfKS, inf);      //������ ���������� �� ������
		Distance[v] = 0;
		for (int i = 0; i < NumberOfKS - 1; ++i)
			for (int j = 0; j < NumberOfPipes; ++j)
				if (Distance[All_edges[j].a] < inf)
					Distance[All_edges[j].b] = min(Distance[All_edges[j].b], Distance[All_edges[j].a] + All_edges[j].cost);
		return Distance[end];
}

int Graph::ConvertKS(int ks_id)    //��������� id ��
{
	for (int i = 0; i < ReNumbered_ks.size(); i++)  
		if (ReNumbered_ks[i] == ks_id)  
			return i;                 //���������� ���������� ����� ��
}

//int Graph::UserChooseKS_inGraph(set<int>& set_ks)
//{
//	for (int i : set_ks)
//		cout << i << " ";       //���������� ��������� �������
//	int choosen_ks;      
	//while ((cin >> choosen_ks).fail() || set_ks.find(choosen_ks) == set_ks.end()) //��������� ���� �� ������������
	//{
	//	cin.clear();
	//	cin.ignore(32767, '\n');
	//	cout << "������� ���������� �����!" << endl;
	//}
//	return ConvertKS(choosen_ks);  //���������� ���������� �����
//}

ofstream& operator<<(ofstream& outf, const Graph& g)
{
	for (int i : g.Pipes_in_Graph)
		outf << i << endl;
	for (int i : g.KS_in_Graph)
		outf << i << endl;
	for (int i = 0; i < g.ReNumbered_ks.size(); i++)
		outf << g.ReNumbered_ks[i] << endl;
	/*for (int i : g.KS_lines)
		outf << i << endl;
	for (int i : g.KS_columns)
		outf << i << endl;*/
	for (int i = 0; i < g.All_edges.size(); i++)
	{
		outf << g.All_edges[i].a << endl;
		outf << g.All_edges[i].b << endl;
		outf << g.All_edges[i].cost << endl;
	}
	return outf;
}
