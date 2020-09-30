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
	string id;
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

bool ChangeStatus(bool b)
{
	b = !b;
	return b;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	pipe p1 = NewPipe();
	KS ks1 = NewKS();
	cout << "������ ������ �����:" << p1.length << endl << "������� ������ �����:" << p1.diametr << endl;
	cout <<"������ �������:" << p1.remont << endl;
	p1.remont = ChangeStatus(p1.remont);
	cout << "����� ������ �������:" << p1.remont << endl;

	cout << "��� ������������� �������:" << ks1.name << endl;
	cout << "���������� ����:" << ks1.number_ceh_inWork << "/" << ks1.number_ceh << endl;
	cout << "������������� ������������� �������" << ks1.efficiency << "%";
	return 0;
}
