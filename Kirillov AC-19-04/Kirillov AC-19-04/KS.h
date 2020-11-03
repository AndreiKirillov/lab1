#pragma once
#include <string>
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
	double GetNuber_ceh() const;
	void SetNumber_ceh(double new_value);
	double GetNumber_ceh_inWork() const;
	void SetNumber_ceh_inWork(double new_value);
};

