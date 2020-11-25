#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Pipe.h"
#include "KS.h"
#include "Source.h"
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
vector<int> FindPipe(const vector<Pipe>& p);   //���������� ����� ������������ �������

void RedactPipe(vector<Pipe>& p)            //������� ��� �������������� �����
{
	if (p.size() == 0)
	{
		cout << "��� ��������� ���� ��� ��������������" << endl;
	}
	else
	{
	    vector<int> pipe_indexes = FindPipe(p);             //������ ������ ��������� ����
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
				ks[id].SetNumber_ceh_inWork(GetNumber(1.0, ks[id].number_ceh));
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;;
				break;
			case 0:
				break;
			}
		} while (WhatToRedact != 0);   //������� �� �����, ����� ������������ ����� 0
	}
}

vector<int> FindPipe(const vector<Pipe>& p)        //������� ���������� ����
{
	cout << "1 - ����� � �������" << endl <<
		"2 - ����� ��� �������" << endl <<
		"3 - ������� ���������� �����" << endl;
	int what_to_find = GetNumber(1, 3);
	vector<int> res;
	int i;
	if (what_to_find==1)
	{
		for (i = 0; i < p.size(); i++)
		{
			if (p[i].remont)      //����� � �������
				res.push_back(i);
		}
	}
	if(what_to_find==2)
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
					res.push_back(id-1);
			} while (id != 0);
		}
	}
	if(res.size()==0)
		cout << "���� �� ������ ���������� �� �������!" << endl;
	return res;
}

template<typename T>                                  //������
using Filter = bool(*)(const KS&, T parametr);        //��������� �� ������� 

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

void SaveData(const vector<Pipe>& p,const vector<KS>& ks)       //�������� ������� ����������
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
		for (i = 0; i < p.size(); i++)           //������� ��������� ������ ����� �� ������ 
		{
			outf << p[i];
		}
		for (i = 0; i < ks.size(); i++)           //������� ��������� ������ �� �� ������ 
		{
			outf << ks[i];
		}
		cout << "������ ������� ���������!" << endl;
	};
	outf.close();
}

void DownloadSaves(vector<Pipe>& p, vector<KS>& ks)         //�������� ������� ��������   
{
	cout << "������� �������� ����� ��� ��������" << endl;
	string filename;
	cin >> filename;
	filename += ".txt";
	ifstream inf;
	int i=0;
	int SizePipes;
	int SizeKS;
	inf.open(filename);
	if (inf.is_open())
	{
		inf >> SizePipes;                       //��������� ���������� ���� � ����������
		inf >> SizeKS;                         //������ ���-�� ��
		if (SizePipes == 0 && SizeKS == 0)    //���� �������� ������� �� ��������� ������ 
		{
			cout << "�� ������� ��������� ������, ���� ����!" << endl;
		}
		else
		{
			p.resize(SizePipes);
			ks.resize(SizeKS);
			for (i = 0; i < p.size(); i++)   //�� ������� ���������� ������ � ������ ����
				inf >> p[i];
			for (i = 0; i < ks.size(); i++)    //�� ������� ���������� ������ � ������ ��
				inf >> ks[i];
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
		"3-�������� ���� ��������" << endl <<
		"4-������������� �����" << endl <<
		"5-������������� ������������� �������" << endl <<
		"6-����� ���� �� �������� '� �������'" << endl <<
		"7-����� ������������� �������" << endl <<
		"8-��������� � ����" << endl <<
		"9-��������� �� �����" << endl <<
		"10-������� ����" << endl <<
		"0-����� �� ���������" << endl;
}

int MakeStep()      // �������, ������������ �����-��������, ������� ����� ��������� ������������
{
	cout << "����� �������� �� ������ �������?" << endl;
	int a = GetNumber(0, 10);
	return a;
}

int main()
{
	setlocale(LC_ALL, "Russian");          //����������� �������� �����
	vector <Pipe> pipes;                       //������ ��� �������� ����
	vector <KS> ks;                            //������ ��� �������� ��
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
		case 3:                                  //����� ������ �������� � �������
			PrintData(pipes, ks);
			break;
		case 4:                                   //����������� ������ "� �������" ��� �����
			RedactPipe(pipes);
			break;
		case 5:                //��������������� ��
			RedactKS(ks);
			break;
		case 6:
		    {
			cout << "����� ���� " << endl;
				vector<int> pipe_indexes = FindPipe(pipes);       //������, �������� ������� ��������� ����
				if (pipe_indexes.size() > 0)                      
				{
					int i;
					for (i = 0; i < pipe_indexes.size(); i++)
						cout << pipes[pipe_indexes[i]];            //������� ��������� �����
				}
		    }
			break;
		case 7:
		{
			vector<int> ks_indexes;                                              //������, �������� ������� ��������� ��
			cout << "1-������ �� �� ��������" << endl << "2-������ �� �� �������� ��������������� �����" << endl;
			int what_to_find = GetNumber(1, 2);
			if (what_to_find == 1)
			{
				cout << "������� ��� ��: ";
				string find_name;
				cin >> find_name;
				ks_indexes=FindKS<string>(ks, CheckByName, find_name);    
			}
			if (what_to_find == 2)
			{
				double procent;
				cout << "������� �������� ������� ��������������� �����: ";
				procent = GetNumber(0.0, 100.0);
				ks_indexes=FindKS(ks, CheckByProcent, procent);
			}
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
		case 8:
			SaveData(pipes, ks);      //���������� ������ � ���� �� �������� ���� � ��
			break;
		case 9:
			DownloadSaves(pipes, ks);    //�������� ������ �� �����
			break;
		case 10:                          //����� ����
			Menu();
			break;
		case 0:
			return 0;
			break;
	    }
    }
}


