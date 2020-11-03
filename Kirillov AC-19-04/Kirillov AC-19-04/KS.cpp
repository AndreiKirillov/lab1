#include "KS.h"
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

void KS::CheckNumber_of_ceh(double CorrectNumber)
{
	do                                      //Проверяем в цикле, чтобы работающих цехов было не больше общего кол-ва цехов
	{
		if (number_ceh < number_ceh_inWork)
		{
			cout << "Введите корректные данные!\n" << endl;
		}
		cout << "Введите общее кол-во цехов:";
		SetNumber_ceh(CorrectNumber);
		cout << "Введите кол-во цехов в работе:";
		SetNumber_ceh_inWork(CorrectNumber);
	} while (number_ceh < number_ceh_inWork);
}

string KS::GetName() const
{
	return name;
}
