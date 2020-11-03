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
	p1.SetLength(GetNumber(1, 10000000));
	cout << "������� ������� �����:";
	p1.SetDiametr(GetNumber(1, 10000000));
	p.push_back(p1);               //��������� � ����� ������� ����
	p[p.size() - 1].SetID(p.size());
}

void NewKS(vector<KS>& ks)                  //������� �������� ����� ������������� �������
{
	KS ks1;
	ks1.SetName();
	cout << "������� ����� ���-�� �����:";
	ks1.SetNumber_ceh(GetNumber(1.0, 100000.0));
	cout << "������� ���-�� ����� � ������:";
	ks1.SetNumber_ceh_inWork(GetNumber(1.0, 100000.0));
	ks1.CheckNumber_of_ceh();
	ks1.SetEfficiency();
	ks.push_back(ks1);                       //��������� ���������� � ����� �������
	ks[ks.size() - 1].SetID(ks.size());
}    

ostream& operator <<(ostream& out,const Pipe& p)    //���������� ��������� ������ ��� �������� ����
{
	out << "ID �����: " << p.GetID();
	out << "\t������ �����: " << p.GetLength();
	out << "\t������� �����: " << p.GetDiametr();
	out << "\t������ �������: " << p.GetRemont() << endl << " " << endl;
	return out;
}

ostream& operator <<(ostream& out,const KS& ks)       //���������� ��������� ������ ��� �������� ��
{
	out << "ID ��: " << ks.GetID();
	out << "\t��� ��: " << ks.GetName();
	out << "\t���������� ����: " << ks.GetNumber_ceh_inWork() << "/" << ks.GetNumber_ceh();
	out << "\t������������� ��: " << ks.GetEfficiency() << "%" << endl << " " << endl;
	return out;
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

void RedactPipe(vector<Pipe>& p)            //������� ��� �������������� �����
{
	if (p.size() == 0)
	{
		cout << "��� ��������� ���� ��� ��������������" << endl;
	}
	else
	{
		cout << "������� ID �����, ������ ������� ������ ������������� (�������� " << 1 << "-" << p.size() << ")" << endl;
		int id = GetNumber(1, p.size());
		p[id-1].ChangeStatus();
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
				ks[id].SetNumber_ceh(GetNumber(1,100000));
				ks[id].CheckNumber_of_ceh();
				ks[id].SetEfficiency();
				break;
			case 3:
				cout << "������� ����� ���-�� ���������� ����� ��:" << endl;
				ks[id].SetNumber_ceh_inWork(GetNumber(1.0, ks[id].GetNumber_ceh()));
				ks[id].CheckNumber_of_ceh();
				ks[id].SetEfficiency();
				break;
			case 0:
				break;
			}
		} while (WhatToRedact != 0);   //������� �� �����, ����� ������������ ����� 0
	}
}

void SaveData(const vector<Pipe>& p,const vector<KS>& ks)       //�������� ������� ����������
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
				outf << p[i].GetID() << endl;
				outf << p[i].GetLength() << endl;
				outf << p[i].GetDiametr() << endl;
				outf << p[i].GetRemont() << endl;
			}
		if (ks.size() > 0)
			for (i = 0; i < ks.size(); i++)           //������� ��������� ������ �� �� ������ 
			{
				outf << ks[i].GetID() << endl;
				outf << ks[i].GetName() << endl;
				outf << ks[i].GetNumber_ceh() << endl;
				outf << ks[i].GetNumber_ceh_inWork() << endl;
				outf << ks[i].GetEfficiency() << endl;
			}
		cout << "������ ������� ���������!" << endl;
	};
	outf.close();
}

void DownloadSaves(vector<Pipe>& p, vector<KS>& ks)         //�������� ������� ��������   
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
					
				/*	inf >> temp;
					p[i].SetID(temp);
					inf >> temp;
					p[i].SetLength(temp);
					inf >> temp;
					p[i].SetDiametr(temp);
					inf >> temp;
					p[i].SetRemont(temp);*/
				}
			}
			if (ks.size() > 0)
			{
				for (i = 0; i < ks.size(); i++)    //�� ������� ���������� ������ � ������ ��
				{
				/*	auto temp;
					inf >> temp;
					ks[i].SetID(temp);
					inf >> temp;
					ks[i].SetName(temp);
					inf >> temp;
					ks[i].SetNumber_ceh(temp);
					inf >> temp;
					ks[i].SetNumber_ceh_inWork(temp);
					inf >> temp;
					ks[i].SetEfficiency(temp);*/
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


