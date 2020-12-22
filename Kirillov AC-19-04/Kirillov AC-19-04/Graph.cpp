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
		cout << "�������� �������� ������������� �������:" << endl;            //////������� ����� ���� �� ���������� �������� ���� ������
		vector<int> end = UserChooseKS(ks, 1);
		int b = end[0];                                                             // �, b, pipe - ������
		cout << "�������� ����� ��� ���������� ������������� �������:" << endl;
		vector<int> v = FindPipe(p, 1);
		int pipe = v[0];   
		if (p[pipe].remont == true || Pipes_in_Graph.find(pipe + 1) != Pipes_in_Graph.end())
		{
			PotentialError = true;            //����� �� ������ ���� � ������� ��� ��� ���� �������������� � ����
			cout << "������ ������������ ������ �����!" << endl;
		}
		if (a >= 0 && b >= 0 && a != b && pipe >= 0 && !PotentialError)       //���� �� ���������
		{
			edge new_edge;
			p[pipe].input = a + 1;       //������ id
			p[pipe].output = b + 1;
			Pipes_in_Graph.insert(pipe + 1); 
			if (KS_in_Graph.find(a+1) != KS_in_Graph.end()) //���� ������ �� ��� ���� � ����
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  //���� ����� ���������� ��� ��
					if (ReNumbered_ks[i] == a+1)
						new_edge.a = i;      //������� ����� ������ ��� ��//������ � ���� ���������� �����
				KS_lines.insert(a + 1);
			}
			else
			{
				KS_in_Graph.insert(a + 1);           //��������� ��������� ������� � ������ ������ ������
				ReNumbered_ks.push_back(a + 1);      //������ ����� �������� � ������� ����� ���������� �������
				new_edge.a = ReNumbered_ks.size() - 1;   
				KS_lines.insert(a + 1);
			}
			//���� ����� ��� �������� ��
			if (KS_in_Graph.find(b+1) != KS_in_Graph.end()) 
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  
					if (ReNumbered_ks[i] == b+1)
						new_edge.b = i;  
				KS_columns.insert(b + 1);
			}
			else
			{
				KS_in_Graph.insert(b + 1);           
				ReNumbered_ks.push_back(b + 1);      
				new_edge.b = ReNumbered_ks.size() - 1;
				KS_columns.insert(b + 1);
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

void Graph::CreateGraph(const vector<Pipe>& p, const vector<KS>& ks)   //������� �������� ������� ���������
{//������������
	if (Pipes_in_Graph.size() == 0)
		EmptyGraph = true;//����������, ��� ���� ������
	else
	{
		//vector<vector<int>> matrix(KS_in_Graph.size(), vector<int>(KS_in_Graph.size()));      //������� ������� ������ �� ���-�� �� � ����
		//for (int i = 0; i < matrix.size(); i++)
		//	for (int j = 0; j < matrix[i].size(); j++)
		//		matrix[i][j] = 0;                //�������� ��� ��������
		//for (auto ed : All_edges)
		//	matrix[ed.a][ConvertKS(ed.b)] = 1;
		//Matrix = matrix;
		vector<vector<int>> matrix(ks.size(), vector<int>(ks.size()));      //������� ������� ������ �� ���-�� �� � ����

		for (int i = 0; i < ks.size(); i++)
			for (int j = 0; j < ks.size(); j++)
				matrix[i][j] = 0;                         //�������� ��� ��������
		for (auto& pipe_id : Pipes_in_Graph)         //���������� �� ������, ��������������� � �����
		{
			matrix[p[pipe_id - 1].input - 1][p[pipe_id - 1].output - 1] = 1;      //��������� �����
		}
		Matrix = matrix;         //����������� ������� ������� ���� ������
		//WeightMatrix = Matrix;
		//for (int pipe : Pipes_in_Graph)    //��������� ������� �����
		//{
		//	WeightMatrix[p[pipe - 1].input][p[pipe - 1].output] = p[pipe - 1].length; //� �������� ���� ����� �����
		//}
	}
}

//bool Graph::CheckLine(int index, string parametr)//��������������� ������� �������� ������/������� �� ���� 
//{
//	if (parametr == "line")//������ ������
//	{
//		for (int j = 0; j < Matrix.size(); j++)
//			if (Matrix[index][j] > 0) //���� ���� ������� �������� �� ���� ���������� true
//				return true;
//	}else
//	if (parametr == "column")//������ �������
//	{
//		for (int i = 0; i < Matrix.size(); i++)
//			if (Matrix[i][index] > 0)
//				return true;
//	}
//	return false;//���� �������� ������ �� �������
//}

void Graph::PrintGraph()        //������� ������ ����� � �������
{
	//������� ������ ���������
	bool Matrix_is_empty = false;
	if (Pipes_in_Graph.size() == 0) 
		Matrix_is_empty = true;
	if (!Matrix_is_empty)        //������� ���� ������, ���� ������� �� ������
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
						cout << i+1 << "\t-\t" << j+1;       //������� id
						endline = true;
					}
					else
						cout << ", " << j+1;
				}
			if (endline)
				cout << endl;
		}
		cout << endl;
	}
	else
		cout << "���������������� ���� �� ����������, ��� ��� ��� ������ ����� �������������� ���������" << endl;
}

void Graph::TopologicalSort()       //������� �������������� ����������
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
			bool VoidLine = true;         //���� ������ ������ � 0
			bool DeletedElement = false;  //���� ������� �������
			for (int j = 0; j < Matrix_Copy[ks-1].size(); j++)   //��������� ������ �� �����������
			{
				if (Matrix_Copy[ks-1][j] == 1)         
					VoidLine = false;
			}
			if (VoidLine == true)    //���� ������ �� �����
			{
				SortedKS.emplace(NumberOfKS, ks); //��������� ������� � ������ ���������������
				NumberOfKS--;                     //���������
				for (int i = 0; i < Matrix_Copy.size(); i++)
					Matrix_Copy[i][ks - 1] = 0;               //�������� �������� �������������� �������
				CopyKS.erase(ks);                 //�������� ������� ��� ��������������
				DeletedElement = true;  
			}
			if (DeletedElement)       //���� ������� �������, �������� ���� ������
				goto skip;         
		}
	} while (NumberOfKS > 0);     
	////������� ���������
	cout << "\t��������������� ����������\t\n\n";
	cout << "� �� - id ��" << endl << endl;
	for(auto& n :SortedKS)
	{
		cout << n.first << "\t" << n.second << endl;
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

int Graph::UserChooseKS_inGraph(set<int>& set_ks)
{
	for (int i : set_ks)
		cout << i << " ";       //���������� ��������� �������
	int choosen_ks;      
	while ((cin >> choosen_ks).fail() || set_ks.find(choosen_ks) == set_ks.end()) //��������� ���� �� ������������
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "������� ���������� �����!" << endl;
	}
	return ConvertKS(choosen_ks);  //���������� ���������� �����
}

bool Graph::CheckCycle()
{
	//bool WhitePeak = true;
	//vector<int> copy_of_ks;
	//for (auto& ks : KS_in_Graph)
	//{
	//	copy_of_ks.push_back(ks);
	//}
	////while (WhitePeak)
	////{
	//	for (int grey_ks : KS_in_Graph)
	//	{
	//		vector<int> GreyPeak;
	//		GreyPeak.push_back(grey_ks - 1);//������ ������ ������� �����
	//		int i=0;
	//		bool possibility = true;
	//		bool grey_peak_found = false;
	//		do
	//		{

	//			if (Matrix[grey_ks - 1][i] == 1)
	//			{
	//				for (auto& it : GreyPeak)
	//					if (i == it)
	//						grey_peak_found = true;
	//				grey_ks = i + 1;
	//			}
	//			i++;
	//		} while (i < Matrix.size() && possibility ==true);
	//		//for (int i = 0; i < Matrix.size(); i++)  //�������� �� ������ � ����� ��������
	//		//{
	//		//	if(Matrix[ks-1][i]!=1 &&)
	//		//	Matrix[ks - 1][i]
	//		//}
	//	}
	////}
	
	int NumberOfKS = KS_in_Graph.size();           //���������������� �������
	vector<vector<int>> Matrix_Copy = Matrix;      //����� ������� ���������, ����� �������� ������
	unordered_set<int> CopyKS = KS_in_Graph;               //����� ������ �����, ����� ������� ��
	set<int> GreyKS;
	int index_i, index_j;
	do//���� ���� ���������������� �������
	{
	skip:                     //����� ��� goto
		for (int ks : CopyKS)      //���������� ���������������� �������
		{
			GreyKS = { -1 };
			GreyKS.insert(ks - 1);//�������� ��������� �������
			bool VoidLine = true;         //���� ������ ������ � 0
			bool DeletedElement = false;  //���� ������� �������
			for (int j = 0; j < Matrix_Copy[ks - 1].size(); j++)   //��������� ������ �� �����������
			{
				if (Matrix_Copy[ks - 1][j] == 1)
					VoidLine = false;
			}
			if (VoidLine == true)    //���� ������ �� �����
			{
				//SortedKS.emplace(NumberOfKS, ks); //��������� ������� � ������ ���������������
				NumberOfKS--;                     //���������
				for (int i = 0; i < Matrix_Copy.size(); i++)
					Matrix_Copy[i][ks - 1] = 0;               //�������� �������� �������������� �������
				CopyKS.erase(ks);                 //�������� ������� ��� ��������������
				DeletedElement = true;
			}
			if (DeletedElement)       //���� ������� �������, �������� ���� ������
				goto skip;
		}
	} while (NumberOfKS > 0);
	
	return false;
}

ofstream& operator<<(ofstream& outf, const Graph& g)
{
	for (int i : g.Pipes_in_Graph)
		outf << i << endl;
	for (int i : g.KS_in_Graph)
		outf << i << endl;
	for (int i = 0; i < g.ReNumbered_ks.size(); i++)
		outf << g.ReNumbered_ks[i] << endl;
	for (int i : g.KS_lines)
		outf << i << endl;
	for (int i : g.KS_columns)
		outf << i << endl;
	for (int i = 0; i < g.All_edges.size(); i++)
	{
		outf << g.All_edges[i].a << endl;
		outf << g.All_edges[i].b << endl;
		outf << g.All_edges[i].cost << endl;
	}
	return outf;
}
