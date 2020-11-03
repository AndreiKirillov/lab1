#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Pipe.h"
#include "KS.h"
#include "Source.h"
using namespace std;

double GetNumber(double min, double max)          //Функция для проверки верного ввода с клавиутуры
{
	double a;
	while ((cin >> a).fail() || a < min || a > max)
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Введите корректное число!" << endl;
	}
	return a;
}

void ChangeStatus(bool& b)   //Функция меняет статус переменной типа bool
{
	b = !b;
}

void NewPipe(vector<pipe>& p)          //Функция создания новой трубы
{
	pipe p1;
	cout << "Введите длину трубы:";
	p1.length = GetNumber(1, 10000000);
	cout << "Введите диаметр трубы:";
	p1.diametr = GetNumber(1, 10000000);
	p1.id = 0;
	p1.remont = false;
	p.push_back(p1);               //Добавляем в конец вектора труб
	p[p.size() - 1].id = p.size();
}

void NewKS(vector<KS>& ks)                  //Функция создания новой компрессорной станции
{
	KS ks1;
	ks1.SetName();
	cout << "Введите общее кол-во цехов:";
	ks1.SetNumber_ceh(GetNumber(1.0, 100000.0));
	cout << "Введите кол-во цехов в работе:";
	ks1.SetNumber_ceh_inWork(GetNumber(1.0, 100000.0));
	ks1.CheckNumber_of_ceh(GetNumber(1.0, 100000.0));
	ks1.SetEfficiency();
	ks.push_back(ks1);                       //добавляем переменную в конец вектора
	ks[ks.size() - 1].SetID(ks.size());
}    

ostream& operator <<(ostream& out,const pipe& p)    //Перегрузка оператора вывода для структур труб
{
	out << "ID трубы:" << p.id << endl;
	out << "Длинна трубы:" << p.length << endl;
	out << "Диаметр трубы:" << p.diametr << endl;
	out << "Статус ремонта:" << p.remont << endl << " " << endl;
	return out;
}

ostream& operator <<(ostream& out,const KS& ks)       //Перегрузка оператора вывода для структур кс
{
	out << "ID КС:" << ks.GetID << endl;
	out << "Имя КС:" << ks.GetName() << endl;
	out << "Работающие цеха:" << ks.number_ceh_inWork << "/" << ks.number_ceh << endl;
	out << "Эффективность компрессорной станции" << ks.efficiency << "%" << endl << " " << endl;
	return out;
}

void PrintData(const vector<pipe>& p,const vector<KS>& ks)   //Функция для вывода данных в консоль
{
	int i;
	cout << "Список труб:" << endl;
	if (p.size() == 0)       //Если вектор труб пуст, ничего не выводим
	{
		cout << "Список труб пуст" << endl << " " << endl;
	}
	else
	{
		for (i = 0; i < p.size(); i++)
		{
			cout << p[i] << endl;      //Используем перегрузку оператора вывода
		}
	}
	cout << "Список компрессорных станций:" << endl;
	if (ks.size() == 0)
	{
		cout << "Список компрессорных станций пуст" << endl << " " << endl;
	}
	else
	{
		for (i = 0; i < ks.size(); i++)
		{
			cout << ks[i] << endl;
		}
	}
}

void RedactPipe(vector<pipe>& p)            //Функция для редактирования трубы
{
	if (p.size() == 0)
	{
		cout << "Нет доступных труб для редактирования" << endl;
	}
	else
	{
		cout << "Введите ID трубы, статус которой хотите редактировать (диапазон " << 1 << "-" << p.size() << ")" << endl;
		int b = p.size();
		int id = GetNumber(1, b)-1;
		ChangeStatus(p[id].remont);
	}
}

void RedactKS(vector<KS>& ks)      //Функция для редактирования кс
{
	if (ks.size() == 0)
	{
		cout << "Нет доступных компрессорных станций для редактирования" << endl;
	}
	else
	{
		cout << "Введите ID компрессорной станции, которую хотите редактировать(диапазон " << 1 << "-" << ks.size() << ")" << endl;
		int b = ks.size();
		int id = GetNumber(1, b)-1;
		cout << "Что именно вы хотите редактировать?" << endl;
		int WhatToRedact;  //Переменная, в неё запишется число, отражающее то что хочет редактировать пользователь
		do
		{
			cout << "1-редактировать имя" << endl << "2-редактировать кол-во цехов" << endl 
				<< "3-редактировать количество работающих цехов" << endl
				<< "0-закончить редактирование" << endl;   //Меню редактирования
			WhatToRedact=GetNumber(0,3);
			switch (WhatToRedact)   //редактируем нужный параметр, в зависимости от переменной
			{
			case 1:
				cout << "Введите новое имя КС:" << endl;
				cin >> ks[id].name;
				break;
			case 2:
				cout << "Введите новое кол-во цехов КС:" << endl;
				ks[id].number_ceh=GetNumber(1,100000);
				if (ks[id].number_ceh < ks[id].number_ceh_inWork)
				{
					cout << "Также нужно уменьшить число работающих цехов, введите новое значение" << endl;
					ks[id].number_ceh_inWork = GetNumber(1.0, ks[id].number_ceh);
				}
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;
				break;
			case 3:
				cout << "Введите новое кол-во работающих цехов КС:" << endl;
				ks[id].number_ceh_inWork = GetNumber(1.0, ks[id].number_ceh);
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;
				break;
			case 0:
				break;
			}
		} while (WhatToRedact != 0);   //Выходим из цикла, когда пользователь введёт 0
	}
}

void SaveData(const vector<pipe>& p,const vector<KS>& ks)       //Описание функции сохранения
{
	ofstream outf;
	int i;
	outf.open("Saves.txt");
	if (p.size() == 0 && ks.size() == 0)   //Когда массивы данных труб и КС пусты, сохранения не произойдёт 
	{
		cout << "Нет данных для сохранения!" << endl;
	}
	else if (outf.is_open())
	{
		outf << p.size() << endl;     //В первую строку выводим кол-во труб
		outf << ks.size() << endl;    //Во вторую кол-во КС
		if (p.size() > 0)                                     
			for (i = 0; i < p.size(); i++)           //Выводим параметры каждой трубы по списку 
			{
				outf << p[i].id << endl;
				outf << p[i].length << endl;
				outf << p[i].diametr << endl;
				outf << p[i].remont << endl;
			}
		if (ks.size() > 0)
			for (i = 0; i < ks.size(); i++)           //Выводим параметры каждой КС по списку 
			{
				outf << ks[i].id << endl;
				outf << ks[i].name << endl;
				outf << ks[i].number_ceh << endl;
				outf << ks[i].number_ceh_inWork << endl;
				outf << ks[i].efficiency << endl;
			}
		cout << "Данные успешно сохранены!" << endl;
	};
	outf.close();
}

void DownloadSaves(vector<pipe>& p, vector<KS>& ks)         //Описание функции загрузки   
{
	ifstream inf;
	int i=0;
	int SizePipes;
	int SizeKS;
	inf.open("Saves.txt");
	if (inf.is_open())
	{
		inf >> SizePipes;                       //Считываем количество труб в переменную
		inf >> SizeKS;                         //Теперь кол-во КС
		if (SizePipes == 0 && SizeKS == 0)    //Если значения нулевые не загружаем данные 
		{
			cout << "Не удалось загрузить данные, файл пуст!" << endl;
		}
		else
		{
			p.resize(SizePipes);
			ks.resize(SizeKS);
			if (p.size() > 0)
			{
				for (i = 0; i < p.size(); i++)   //По порядку записываем данные в массив труб
				{
					inf >> p[i].id;
					inf >> p[i].length;
					inf >> p[i].diametr;
					inf >> p[i].remont;
				}
			}
			if (ks.size() > 0)
			{
				for (i = 0; i < ks.size(); i++)    //По порядку записываем данные в массив КС
				{
					inf >> ks[i].id;
					inf >> ks[i].name;
					inf >> ks[i].number_ceh;
					inf >> ks[i].number_ceh_inWork;
					inf >> ks[i].efficiency;
				}
			}
		}
	}
	inf.close();
	cout << "Загрузка прошла успешно" << endl;
}

void Menu()          //Функция вывода меню, выводит список возможных действий пользователя
{
	cout << "Меню программы" << endl <<
		"1-Добавить трубу" << endl <<
		"2-Добавить компрессорную станцию" << endl <<
		"3-Просмотр всех объектов" << endl <<
		"4-Редактировать трубу" << endl <<
		"5-Редактировать компрессорную станцию" << endl <<
		"6-Сохранить в файл" << endl <<
		"7-Загрузить из файла" << endl <<
		"8-Открыть меню" << endl <<
		"0-Выход из программы" << endl;
}

int MakeStep()      // Функция, возвращающая число-действие, которое хочет совершить пользователь
{
	cout << "Какое действие вы хотите сделать?" << endl;
	int a = GetNumber(0, 8);
	return a;
}

int main()
{
	setlocale(LC_ALL, "Russian");              //Подключение русского языка
	vector <pipe> pipes;                       //вектор для хранения труб
	vector <KS> ks;                            //вектор для хранения КС
	Menu();                                  //показываем меню            
	while (1)                   
	{
		int operation = MakeStep();          //Запрашиваем действие пользователя
		switch (operation)                   //цикл для обработки операций, выбранных пользователем
		{
		case 1:                  
			NewPipe(pipes);  //Создаем новую трубу
			break;
		case 2:
			NewKS(ks);        //Создаем новую кс
			break;
		case 3:                                  //Вывод списка объектов в консоль
			PrintData(pipes, ks);
			break;
		case 4:                                   //Редактируем статус "В ремонте" для трубы
			RedactPipe(pipes);
			break;
		case 5:                //Рекдактирование КС
			RedactKS(ks);
			break;
		case 6:
			SaveData(pipes, ks);      //Сохранение данных в файл из массивов труб и КС
			break;
		case 7:
			DownloadSaves(pipes, ks);    //загрузка данных из файла
			break;
		case 8:                          //Показ меню
			Menu();
			break;
		case 0:
			return 0;
			break;
	    }
    }
}


