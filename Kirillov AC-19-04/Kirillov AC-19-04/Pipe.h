#pragma once
#include <iostream>
#include <fstream>

class Pipe
{
private:
	int id;
	int length;
	int diametr;
	bool remont;
public:
	Pipe();
	int GetID() const;
	void SetID(int new_id);
	int GetLength() const;
	void SetLength(int new_length);
	int GetDiametr() const;
	void SetDiametr(int new_diametr);
	bool GetRemont() const;
	void SetRemont(bool new_status);
	void ChangeStatus();
	friend std::ostream& operator <<(std::ostream& out, const Pipe& p);     //Для вывода полей класса в консоль
	friend std::ifstream& operator >>(std::ifstream& inf, Pipe& p);         //Для ввода полей класса из файла
	friend std::ofstream& operator <<(std::ofstream& outf, const Pipe& p);   //Для вывода полей класса в файл
};

