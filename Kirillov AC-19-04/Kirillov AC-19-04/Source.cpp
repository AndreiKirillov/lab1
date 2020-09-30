#include <iostream>
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
	while (a < 0 || a > 7)
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
	while (a < 0 || a > 7)
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

int main()
{
	setlocale(LC_ALL, "Russian");
	pipe pipes[100];
	KS ks[100];
	int NumberPipe = 0;
	int NumberKS = 0;
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
		    	cout << "������ ���� ����" << endl;
	    	}
	    	else
	    	{
	    		int i;
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
	    		cout << "������ ������������� ������� ����" << endl;
	    	}
	    	else
	    	{
	    		int j;
	    		for (j = 1; j < NumberKS + 1; j++)
	    		{
	    			cout << "ID ��:" << ks[j].id << endl;
	    			cout << "��� ��:" << ks[j].name << endl;
	    			cout << "���������� ����:" << ks[j].number_ceh_inWork << "/" << ks[j].number_ceh << endl;
	    			cout << "������������� ������������� �������" << ks[j].efficiency << "%" << endl << " " << endl;
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
	    }
		operation = MakeStep();
    }
	return 0;
}
