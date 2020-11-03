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

void ChangeStatus(bool& b)   //������� ������ ������ ���������� ���� bool
{
	b = !b;
}

void NewPipe(vector<pipe>& p)          //������� �������� ����� �����
{
	pipe p1;
	cout << "������� ����� �����:";
	p1.length = GetNumber(1, 10000000);
	cout << "������� ������� �����:";
	p1.diametr = GetNumber(1, 10000000);
	p1.id = 0;
	p1.remont = false;
	p.push_back(p1);               //��������� � ����� ������� ����
	p[p.size() - 1].id = p.size();
}

void NewKS(vector<KS>& ks)                  //������� �������� ����� ������������� �������
{
	KS ks1;
	ks1.SetName();
	cout << "������� ����� ���-�� �����:";
	ks1.SetNumber_ceh(GetNumber(1.0, 100000.0));
	cout << "������� ���-�� ����� � ������:";
	ks1.SetNumber_ceh_inWork(GetNumber(1.0, 100000.0));
	ks1.CheckNumber_of_ceh(GetNumber(1.0, 100000.0));
	ks1.SetEfficiency();
	ks.push_back(ks1);                       //��������� ���������� � ����� �������
	ks[ks.size() - 1].SetID(ks.size());
}    

ostream& operator <<(ostream& out,const pipe& p)    //���������� ��������� ������ ��� �������� ����
{
	out << "ID �����:" << p.id << endl;
	out << "������ �����:" << p.length << endl;
	out << "������� �����:" << p.diametr << endl;
	out << "������ �������:" << p.remont << endl << " " << endl;
	return out;
}

ostream& operator <<(ostream& out,const KS& ks)       //���������� ��������� ������ ��� �������� ��
{
	out << "ID ��:" << ks.GetID << endl;
	out << "��� ��:" << ks.GetName() << endl;
	out << "���������� ����:" << ks.number_ceh_inWork << "/" << ks.number_ceh << endl;
	out << "������������� ������������� �������" << ks.efficiency << "%" << endl << " " << endl;
	return out;
}

void PrintData(const vector<pipe>& p,const vector<KS>& ks)   //������� ��� ������ ������ � �������
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

void RedactPipe(vector<pipe>& p)            //������� ��� �������������� �����
{
	if (p.size() == 0)
	{
		cout << "��� ��������� ���� ��� ��������������" << endl;
	}
	else
	{
		cout << "������� ID �����, ������ ������� ������ ������������� (�������� " << 1 << "-" << p.size() << ")" << endl;
		int b = p.size();
		int id = GetNumber(1, b)-1;
		ChangeStatus(p[id].remont);
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
		int b = ks.size();
		int id = GetNumber(1, b)-1;
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
				cout << "������� ����� ��� ��:" << endl;
				cin >> ks[id].name;
				break;
			case 2:
				cout << "������� ����� ���-�� ����� ��:" << endl;
				ks[id].number_ceh=GetNumber(1,100000);
				if (ks[id].number_ceh < ks[id].number_ceh_inWork)
				{
					cout << "����� ����� ��������� ����� ���������� �����, ������� ����� ��������" << endl;
					ks[id].number_ceh_inWork = GetNumber(1.0, ks[id].number_ceh);
				}
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;
				break;
			case 3:
				cout << "������� ����� ���-�� ���������� ����� ��:" << endl;
				ks[id].number_ceh_inWork = GetNumber(1.0, ks[id].number_ceh);
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;
				break;
			case 0:
				break;
			}
		} while (WhatToRedact != 0);   //������� �� �����, ����� ������������ ����� 0
	}
}

void SaveData(const vector<pipe>& p,const vector<KS>& ks)       //�������� ������� ����������
{
	ofstream outf;
	int i;
	outf.open("Saves.txt");
	if (p.size() == 0 && ks.size() == 0)   //����� ������� ������ ���� � �� �����, ���������� �� ��������� 
	{
		cout << "��� ������ ��� ����������!" << endl;
	}
	else if (outf.is_open())
	{
		outf << p.size() << endl;     //� ������ ������ ������� ���-�� ����
		outf << ks.size() << endl;    //�� ������ ���-�� ��
		if (p.size() > 0)                                     
			for (i = 0; i < p.size(); i++)           //������� ��������� ������ ����� �� ������ 
			{
				outf << p[i].id << endl;
				outf << p[i].length << endl;
				outf << p[i].diametr << endl;
				outf << p[i].remont << endl;
			}
		if (ks.size() > 0)
			for (i = 0; i < ks.size(); i++)           //������� ��������� ������ �� �� ������ 
			{
				outf << ks[i].id << endl;
				outf << ks[i].name << endl;
				outf << ks[i].number_ceh << endl;
				outf << ks[i].number_ceh_inWork << endl;
				outf << ks[i].efficiency << endl;
			}
		cout << "������ ������� ���������!" << endl;
	};
	outf.close();
}

void DownloadSaves(vector<pipe>& p, vector<KS>& ks)         //�������� ������� ��������   
{
	ifstream inf;
	int i=0;
	int SizePipes;
	int SizeKS;
	inf.open("Saves.txt");
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
			if (p.size() > 0)
			{
				for (i = 0; i < p.size(); i++)   //�� ������� ���������� ������ � ������ ����
				{
					inf >> p[i].id;
					inf >> p[i].length;
					inf >> p[i].diametr;
					inf >> p[i].remont;
				}
			}
			if (ks.size() > 0)
			{
				for (i = 0; i < ks.size(); i++)    //�� ������� ���������� ������ � ������ ��
				{
					inf >> ks[i].id;
					inf >> ks[i].name;
					inf >> ks[i].number_ceh;
					inf >> ks[i].number_ceh_inWork;
					inf >> ks[i].efficiency;
				}
			}
		}
	}
	inf.close();
	cout << "�������� ������ �������" << endl;
}

void Menu()          //������� ������ ����, ������� ������ ��������� �������� ������������
{
	cout << "���� ���������" << endl <<
		"1-�������� �����" << endl <<
		"2-�������� ������������� �������" << endl <<
		"3-�������� ���� ��������" << endl <<
		"4-������������� �����" << endl <<
		"5-������������� ������������� �������" << endl <<
		"6-��������� � ����" << endl <<
		"7-��������� �� �����" << endl <<
		"8-������� ����" << endl <<
		"0-����� �� ���������" << endl;
}

int MakeStep()      // �������, ������������ �����-��������, ������� ����� ��������� ������������
{
	cout << "����� �������� �� ������ �������?" << endl;
	int a = GetNumber(0, 8);
	return a;
}

int main()
{
	setlocale(LC_ALL, "Russian");              //����������� �������� �����
	vector <pipe> pipes;                       //������ ��� �������� ����
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
			SaveData(pipes, ks);      //���������� ������ � ���� �� �������� ���� � ��
			break;
		case 7:
			DownloadSaves(pipes, ks);    //�������� ������ �� �����
			break;
		case 8:                          //����� ����
			Menu();
			break;
		case 0:
			return 0;
			break;
	    }
    }
}


