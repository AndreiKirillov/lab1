#include "Pipe.h"
#include <iostream>
#include <fstream>
using namespace std;

int Pipe::MAX_ID = 1;

Pipe::Pipe()
{
	id = MAX_ID;
	length = 0;
	diametr = 0;
	remont = 0;
	input = 0;
	output = 0;
	MAX_ID++;
}

void Pipe::ChangeStatus()   //������ ������ �������
{
	remont=!remont;
}

ostream& operator <<(ostream& out, const Pipe& p)    //���������� ��������� ������ ��� �������� ����
{
	out << "ID �����: " << p.id;
	out << "\t������ �����: " << p.length;
	out << "\t������� �����: " << p.diametr;
	out << "\t������ �������: " << p.remont << "\n";
	if (p.input != 0 && p.output != 0)
	{
		out << "����� ��������� " << p.input << " �� � " << p.output << " ��" << endl;
	}
	return out;
}

ifstream& operator>>(ifstream& inf, Pipe& p)
{
	inf >> p.id;
	inf >> p.length;
	inf >> p.diametr;
	inf >> p.remont;
	inf >> p.input;
	inf >> p.output;
	return inf;
}

ofstream& operator<<(ofstream& outf, const Pipe& p)
{
	outf << p.id << endl;
	outf << p.length << endl;
	outf << p.diametr << endl;
	outf << p.remont << endl;
	outf << p.input << endl;
	outf << p.output << endl;
	return outf;
}
