#pragma once
#include <iostream>
#include <fstream>

class Pipe
{
public:
	int id;
	int length;
	int diametr;
	bool remont;
	int input;
	int output;
	Pipe();
	void ChangeStatus();
	friend std::ostream& operator <<(std::ostream& out, const Pipe& p);     //Для вывода полей класса в консоль
	friend std::ifstream& operator >>(std::ifstream& inf, Pipe& p);         //Для ввода полей класса из файла
	friend std::ofstream& operator <<(std::ofstream& outf, const Pipe& p);   //Для вывода полей класса в файл
};

