#include "Graph.h"
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include <vector>
#include<set>

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
			p[pipe].input = a + 1;       //������ id
			p[pipe].output = b + 1;
			Pipes_in_Graph.insert(pipe + 1);
			KS_in_Graph.insert(a + 1);
			KS_in_Graph.insert(b + 1);
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
{
	vector<vector<int>> matrix(ks.size(), vector<int>(ks.size()));      //������� ������� ������ �� ���-�� �� � ����
	for (int i = 0; i < ks.size(); i++)
		for (int j = 0; j < ks.size(); j++)
			matrix[i][j] = 0;                         //�������� ��� ��������
	for (auto &pipe_id : Pipes_in_Graph)         //���������� �� ������, ��������������� � �����
	{
		matrix[p[pipe_id-1].input - 1][p[pipe_id-1].output - 1] = 1;      //��������� �����
	}
	Matrix = matrix;         //����������� ������� ������� ���� ������
}

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
						cout << ", " << j;
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
	set<int> CopyKS = KS_in_Graph;               //����� ������ �����, ����� ������� ��
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
	//return map<int, int>();
}

//bool Graph::CheckCycle()
//{
//	/*for (int a = 0; a < Matrix.size(); a++)
//		for (int b = 0; b < Matrix[a].size(); b++)
//		{
//			bool WhitePeak = true;
//			if(Matrix[a][b]=1)
//			{
//				do
//				{
//
//				}while(WhitePeak)
//			}
//		}*/
//	bool WhitePeak = true;
//	vector<int> copy_of_ks;
//	for (auto& ks : KS_in_Graph)
//	{
//		copy_of_ks.push_back(ks);
//	}
//	//while (WhitePeak)
//	//{
//		for (int grey_ks : KS_in_Graph)
//		{
//			vector<int> GreyPeak;
//			GreyPeak.push_back(grey_ks - 1);//������ ������ ������� �����
//			int i=0;
//			bool possibility = true;
//			bool grey_peak_found = false;
//			do
//			{
//
//				if (Matrix[grey_ks - 1][i] == 1)
//				{
//					for (auto& it : GreyPeak)
//						if (i == it)
//							grey_peak_found = true;
//					grey_ks = i + 1;
//				}
//				i++;
//			} while (i < Matrix.size() && possibility ==true);
//			//for (int i = 0; i < Matrix.size(); i++)  //�������� �� ������ � ����� ��������
//			//{
//			//	if(Matrix[ks-1][i]!=1 &&)
//			//	Matrix[ks - 1][i]
//			//}
//		}
//	//}
//	return false;
//}
