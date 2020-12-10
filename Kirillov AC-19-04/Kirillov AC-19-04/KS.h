#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class KS
{
public:
	int id;
	string name;
	double number_ceh;
	double number_ceh_inWork;
	double efficiency;
	KS();
	void SetName();
	void SetNumber_ceh(double new_value);
	void SetNumber_ceh_inWork(double new_value);
	friend ostream& operator <<(ostream& out, const KS& ks);       //���������� ��������� ������ ��� �������� ��
	friend ifstream& operator >>(ifstream& inf, KS& ks);
	friend ofstream& operator <<(ofstream& outf, const KS& ks);
};

