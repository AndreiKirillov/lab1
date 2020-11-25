#include "Pipe.h"
#include <iostream>
#include <fstream>
using namespace std;

Pipe::Pipe()
{
	id = 0;
	length = 0;
	diametr = 0;
	remont = 0;
}

//int Pipe::GetID() const
//{
//	return id;
//}
//
//void Pipe::SetID(int new_id)
//{
//	id = new_id;
//}
//
//int Pipe::GetLength() const
//{
//	return length;
//}
//
//void Pipe::SetLength(int new_length)
//{
//	length = new_length;
//}
//
//int Pipe::GetDiametr() const
//{
//	return diametr;
//}
//
//void Pipe::SetDiametr(int new_diametr)
//{
//	diametr = new_diametr;
//}
//
//bool Pipe::GetRemont() const
//{
//	return remont;
//}
//
//void Pipe::SetRemont(bool new_status)
//{
//	remont = new_status;
//}

void Pipe::ChangeStatus()   //Меняем статус ремонта
{
	remont=!remont;
}

ostream& operator <<(ostream& out, const Pipe& p)    //Перегрузка оператора вывода для структур труб
{
	out << "ID трубы: " << p.id;
	out << "\tДлинна трубы: " << p.length;
	out << "\tДиаметр трубы: " << p.diametr;
	out << "\tСтатус ремонта: " << p.remont << "\n\n";
	return out;
}

ifstream& operator>>(ifstream& inf, Pipe& p)
{
	inf >> p.id;
	inf >> p.length;
	inf >> p.diametr;
	inf >> p.remont;
	return inf;
}

ofstream& operator<<(ofstream& outf, const Pipe& p)
{
	outf << p.id << endl;
	outf << p.length << endl;
	outf << p.diametr << endl;
	outf << p.remont << endl;
	return outf;
}
