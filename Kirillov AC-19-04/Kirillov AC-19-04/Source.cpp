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
	cout << "¬ведите длину трубы:";
	cin >> pipe1.length;
	cout << "¬ведите диаметр трубы:";
	cin >> pipe1.diametr;
	pipe1.id = 0;
	pipe1.remont = false;
	return pipe1;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	pipe p1 = NewPipe();
	cout << "ƒлинна данной трубы:" << p1.length << endl << "ƒиаметр данной трубы:" << p1.diametr << endl;
	return 0;
}
