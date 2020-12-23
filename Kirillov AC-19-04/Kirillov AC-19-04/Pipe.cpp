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

void Pipe::ChangeStatus()   //Меняем статус ремонта
{
	remont=!remont;
}

ostream& operator <<(ostream& out, const Pipe& p)    //Перегрузка оператора вывода для структур труб
{
	out << "ID трубы: " << p.id;
	out << "\tДлинна трубы: " << p.length;
	out << "\tДиаметр трубы: " << p.diametr;
	out << "\tСтатус ремонта: " << p.remont << "\n";
	if (p.input != 0 && p.output != 0)
	{
		out << "Труба соединяет " << p.input << " кс и " << p.output << " кс" << endl;
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
