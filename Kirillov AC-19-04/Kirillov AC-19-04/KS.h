#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class KS
{
private:
	int id;
	string name;
	double number_ceh;
	double number_ceh_inWork;
	double efficiency;
public:
	KS();
	int GetID() const;
	void SetID(int new_id);
	string GetName() const;
	void SetName();
	double GetNumber_ceh() const;
	void SetNumber_ceh(double new_value);
	double GetNumber_ceh_inWork() const;
	void SetNumber_ceh_inWork(double new_value);
	double GetEfficiency() const;
	void SetEfficiency();
	void CheckNumber_of_ceh();                       //Для проверки корректности кол-ва цехов
	friend ostream& operator <<(ostream& out, const KS& ks);       //Перегрузка оператора вывода для структур кс
	friend ifstream& operator >>(ifstream& inf, KS& ks);
	friend ofstream& operator <<(ofstream& outf, const KS& ks);
};

