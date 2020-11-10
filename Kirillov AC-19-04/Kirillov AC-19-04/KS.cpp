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

int KS::GetID() const
{
	return id;
}

void KS::SetID(int new_id)
{
	id = new_id;
}


void KS::SetName()
{
	string NewName;
	cout << "Введите имя компрессорной станции:";
	cin.ignore(32767, '\n');
	getline(cin, NewName );
	name = NewName;
}

double KS::GetNumber_ceh() const
{
	return number_ceh;
}

void KS::SetNumber_ceh(double new_value)
{
	number_ceh = new_value;
}

double KS::GetNumber_ceh_inWork() const
{
	return number_ceh_inWork;
}

void KS::SetNumber_ceh_inWork(double new_value)
{
	number_ceh_inWork = new_value;
}

double KS::GetEfficiency() const
{
	return efficiency;
}

void KS::SetEfficiency()
{
	efficiency= (number_ceh_inWork / number_ceh) * 100;
}

void KS::CheckNumber_of_ceh()
{
	do                                      //Проверяем в цикле, чтобы работающих цехов было не больше общего кол-ва цехов
	{
		if (number_ceh < number_ceh_inWork)
		{
			cout << "Введите корректные данные!\n" << endl;
			cout << "Введите общее кол-во цехов:" << endl;
			SetNumber_ceh(GetNumber(1.0, 100000.0));
			cout << "Введите кол-во цехов в работе:" << endl;
			SetNumber_ceh_inWork(GetNumber(1.0, 100000.0));
		}
	} while (number_ceh < number_ceh_inWork);
}

string KS::GetName() const
{
	return name;
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
