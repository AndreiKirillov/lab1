#include "Pipe.h"
#include <iostream>

Pipe::Pipe()
{
	id = 0;
	length = 0;
	diametr = 0;
	remont = 0;
}

int Pipe::GetID() const
{
	return id;
}

void Pipe::SetID(int new_id)
{
	id = new_id;
}

int Pipe::GetLength() const
{
	return length;
}

void Pipe::SetLength(int new_length)
{
	length = new_length;
}

int Pipe::GetDiametr() const
{
	return diametr;
}

void Pipe::SetDiametr(int new_diametr)
{
	diametr = new_diametr;
}

bool Pipe::GetRemont() const
{
	return remont;
}

void Pipe::SetRemont(bool new_status)
{
	remont = new_status;
}

void Pipe::ChangeStatus()   //Меняем статус ремонта
{
	remont=!remont;
}

std::ostream& operator <<(std::ostream& out, const Pipe& p)    //Перегрузка оператора вывода для структур труб
{
	out << "ID трубы: " << p.id;
	out << "\tДлинна трубы: " << p.length;
	out << "\tДиаметр трубы: " << p.diametr;
	out << "\tСтатус ремонта: " << p.remont;
	return out;
}
