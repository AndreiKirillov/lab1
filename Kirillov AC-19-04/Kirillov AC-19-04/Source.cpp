#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipe
{
	int id;
	int length;
	int diametr;
	bool remont;
};

struct KS
{
	int id;
	string name;
	float number_ceh;
	float number_ceh_inWork;
	float efficiency;
};

ifstream inf;
int NumberPipe = 0;
int NumberKS = 0;

pipe NewPipe()
{
	pipe pipe1;
	cout << "������� ����� �����:";
	cin >> pipe1.length;
	cout << "������� ������� �����:";
	cin >> pipe1.diametr;
	pipe1.id = 0;
	pipe1.remont = false;
	return pipe1;
}

KS NewKS()
{
	KS ks1;
	cout << "������� ��� ������������� �������:";
	cin.ignore(32767, '\n');                                        //���� � https://ravesli.com/urok-57-vvedenie-v-std-string/
	getline(cin, ks1.name);
	cout << "������� ����� ���-�� ����� � ����� � ������ ����� ������:";
	cin >> ks1.number_ceh >> ks1.number_ceh_inWork;
	ks1.efficiency = (ks1.number_ceh_inWork / ks1.number_ceh) * 100;
	return ks1;
}

int Menu()
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
		"0-����� �� ���������" << endl<<
		"��� �� ������ �������?"<<endl;
	int a;
	cin >> a;
	while (a < 0 || a > 8)
	{
		cout << "������� ������ �����!" << endl;
		cin >> a;
	}
	return a;
}

int MakeStep()
{
	cout << "����� �������� �� ������ �������?" << endl;
	int a;
	cin >> a;
	while (a < 0 || a > 8)
	{
		cout << "������� ������ �����!" << endl;
		cin >> a;
	}
	return a;
}

bool ChangeStatus(bool b)
{
	b = !b;
	return b;
}

void DownloadSaves(pipe p[100],KS k[1]);

int main()
{
	setlocale(LC_ALL, "Russian");
	pipe pipes[100];
	KS ks[100];
	cout << "�� ������ ��������� ����������� ������? [y/n]" << endl;
	char ch;
	cin >> ch;
	if (ch == 'y' || ch == '1')
		DownloadSaves(pipes, ks);
	else if (ch = 'n' || ch == '0')
		cout << " " << endl;
	else
		cout << "������! �� ������ ��������� ������ �����, ��������� '7'" << " " << endl;
	
	int i;
	ofstream outf;
	int operation = Menu();
	while (operation != 0)
	{
		switch (operation)
		{
		case 1:
			NumberPipe++;
			pipes[NumberPipe] = NewPipe();
			pipes[NumberPipe].id = NumberPipe;
			break;
		case 2:
			NumberKS++;
			ks[NumberKS] = NewKS();
			ks[NumberKS].id = NumberKS;
			break;
		case 3:
			cout << "������ ����:" << endl;
			if (NumberPipe == 0)
			{
				cout << "������ ���� ����" << endl << " " << endl;
			}
			else
			{
				for (i = 1; i < NumberPipe + 1; i++)
				{
					cout << "ID �����:" << pipes[i].id << endl;
					cout << "������ �����:" << pipes[i].length << endl;
					cout << "������� �����:" << pipes[i].diametr << endl;
					cout << "������ �������:" << pipes[i].remont << endl << " " << endl;
				}
			}
			cout << "������ ������������� �������:" << endl;
			if (NumberKS == 0)
			{
				cout << "������ ������������� ������� ����" << endl << " " << endl;
			}
			else
			{
				for (i = 1; i < NumberKS + 1; i++)
				{
					cout << "ID ��:" << ks[i].id << endl;
					cout << "��� ��:" << ks[i].name << endl;
					cout << "���������� ����:" << ks[i].number_ceh_inWork << "/" << ks[i].number_ceh << endl;
					cout << "������������� ������������� �������" << ks[i].efficiency << "%" << endl << " " << endl;
				}
			}
			break;
		case 4:
			cout << "������� ID �����, ������ ������� ������ �������������:" << endl;
			int b;
			cin >> b;
			while (b < 1 || b > NumberPipe)
			{
				cout << "����� ����� �� ����������! ������� ������ ID" << endl;
				cin >> b;
			}
			pipes[b].remont = ChangeStatus(pipes[b].remont);
			break;
		case 5:
			cout << "������� ID ������������� �������, ������� ������ �������������:" << endl;
			int a;
			cin >> a;
			while (a < 1 || a > NumberKS)
			{
				cout << "����� ����� �� ����������! ������� ������ ID" << endl;
				cin >> a;
			}
			cout << "��� ������ �� ������ �������������?" << endl;
			int WhatToRedact;
			do
			{
				cout << "1-������������� ���" << endl << "2-������������� ���-�� �����" << endl << "3-������������� ���������� ���������� �����" << endl
					<< "0-��������� ��������������" << endl;
				cin >> WhatToRedact;
				while (WhatToRedact < 0 || WhatToRedact>3)
				{
					cout << "������ �������� �� ����������, ������� ����������" << endl;
					cin >> WhatToRedact;
				}
				switch (WhatToRedact)
				{
				case 1:
					cout << "������� ����� ��� ��:" << endl;
					cin >> ks[a].name;
					break;
				case 2:
					cout << "������� ����� ���-�� ����� ��:" << endl;
					cin >> ks[a].number_ceh;
					ks[a].efficiency = (ks[a].number_ceh_inWork / ks[a].number_ceh) * 100;
					break;
				case 3:
					cout << "������� ����� ���-�� ���������� ����� ��:" << endl;
					cin >> ks[a].number_ceh_inWork;
					ks[a].efficiency = (ks[a].number_ceh_inWork / ks[a].number_ceh) * 100;
					break;
				case 0:
					break;
				}

			} while (WhatToRedact != 0);
			break;
		case 6:
			outf.open("Saves.txt");
			if (NumberPipe == 0 && NumberKS == 0)
			{
				cout << "��� ������ ��� ����������!" << endl;
			}
			else
			{
				outf << NumberPipe << endl;
				outf << NumberKS << endl;
				i = 1;
				while (i <= NumberPipe)
				{
					outf << pipes[i].id << endl;
					outf << pipes[i].length << endl;
					outf << pipes[i].diametr << endl;
					outf << pipes[i].remont << endl;
					i++;
				}
				i = 1;
				while (i <= NumberKS)
				{
					outf << ks[i].id << endl;
					outf << ks[i].name << endl;
					outf << ks[i].number_ceh << endl;
					outf << ks[i].number_ceh_inWork << endl;
					outf << ks[i].efficiency << endl;
					i++;
				}
			};
			outf.close();
			cout << "������ ������� ���������!" << endl;
			break;
		case 7:
			DownloadSaves(pipes, ks);
			break;
		case 8:
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
			break;
	
	    }
		operation = MakeStep();
    }
	return 0;
}

void DownloadSaves(pipe p[100], KS k[100])
{
	int i;
	inf.open("Saves.txt");
	inf >> NumberPipe;
	inf >> NumberKS;
	if (NumberPipe == 0 && NumberKS == 0)
	{
		cout << "�� ������� ��������� ������, ���� ����!" << endl;
	}
	else
	{
		i = 1;
		while (i <= NumberPipe)
		{
			inf >> p[i].id;
			inf >> p[i].length;
			inf >> p[i].diametr;
			inf >> p[i].remont;
			i++;
		}
		i = 1;
		while (i <= NumberKS)
		{
			inf >> k[i].id;
			inf >> k[i].name;
			inf >> k[i].number_ceh;
			inf >> k[i].number_ceh_inWork;
			inf >> k[i].efficiency;
			i++;
		}
	}
	inf.close();
	cout << "�������� ������ �������" << endl;
}
