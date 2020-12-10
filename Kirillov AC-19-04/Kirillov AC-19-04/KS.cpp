#include "KS.h"
#include "Source.h"
#include <iostream>
#include <string>
using namespace std;

KS::KS()
{
	id = 0;
	name = "Unknown";
	number_ceh = 0;
	number_ceh_inWork = 0;
	efficiency = 0;
}

void KS::SetName()
{
	string NewName;
	cout << "Введите имя компрессорной станции:";
	cin.ignore(32767, '\n');
	getline(cin, NewName );
	name = NewName;
}

void KS::SetNumber_ceh(double new_value)
{
	if (new_value < number_ceh_inWork)
	{
		cout << "Кол-во цехов должно быть больше или равно чем кол-во работающих цехов (больше " << number_ceh_inWork << ")" << endl;
		new_value = GetNumber(number_ceh_inWork, 10000.0);
	}
	number_ceh = new_value;
}

void KS::SetNumber_ceh_inWork(double new_value)
{
	if (new_value > number_ceh)
	{
		cout << "Кол-во работающих цехов должно быть меньше или равно общего кол-ва цехов (меньше " << number_ceh << ")" << endl;
		new_value = GetNumber(0.0, number_ceh);
	}
	number_ceh_inWork = new_value;
}

ostream& operator <<(ostream& out, const KS& ks)       //Перегрузка оператора вывода для структур кс
{
	out << "ID КС: " << ks.id;
	out << "\tИмя КС: " << ks.name;
	out << "\tРаботающие цеха: " << ks.number_ceh_inWork << "/" << ks.number_ceh;
	out << "\tЭффективность КС: " << ks.efficiency << "%" << endl << endl;
	return out;
}

ifstream& operator>>(ifstream& inf, KS& ks)
{
	inf >> ks.id;
	inf >> ks.name;
	inf >> ks.number_ceh;
	inf >> ks.number_ceh_inWork;
	inf >> ks.efficiency;
	return inf;
}

ofstream& operator<<(ofstream& outf, const KS& ks)
{
	outf << ks.id << endl;
	outf << ks.name << endl;
	outf << ks.number_ceh << endl;
	outf << ks.number_ceh_inWork << endl;
	outf << ks.efficiency << endl;
	return outf;
}
