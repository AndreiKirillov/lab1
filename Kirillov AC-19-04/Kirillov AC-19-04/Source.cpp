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
	int number_ceh;
	int number_ceh_inWork;
	int efficiency;
};

pipe NewPipe()
{
	pipe pipe1;
	cout << "Введите длину трубы:";
	cin >> pipe1.length;
	cout << "Введите диаметр трубы:";
	cin >> pipe1.diametr;
	pipe1.id = 0;
	pipe1.remont = false;
	return pipe1;
}

void ChangeStatus(bool b)
{
	b = !b;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	pipe p1 = NewPipe();
	cout << "Длинна данной трубы:" << p1.length << endl << "Диаметр данной трубы:" << p1.diametr << endl;
	cout <<"Статус ремонта:" << p1.remont << endl;
	ChangeStatus(p1.remont);
	cout << "Новый статус ремонта:" << p1.remont << endl;
	return 0;
}
