#include "Pipe.h"

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

void Pipe::ChangeStatus()
{
	!remont;
}
