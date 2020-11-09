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

void NewPipe(vector<Pipe>& p)          //Функция создания новой трубы
{
	Pipe p1;
	cout << "Введите длину трубы:";
	p1.SetLength(GetNumber(1, 10000000));
	cout << "Введите диаметр трубы:";
	p1.SetDiametr(GetNumber(1, 10000000));
	p.push_back(p1);               //Добавляем в конец вектора труб
	p[p.size() - 1].SetID(p.size());
}

void NewKS(vector<KS>& ks)                  //Функция создания новой компрессорной станции
{
	KS ks1;
	ks1.SetName();
	cout << "Введите общее кол-во цехов:";
	ks1.SetNumber_ceh(GetNumber(1.0, 100000.0));
	cout << "Введите кол-во цехов в работе:";
	ks1.SetNumber_ceh_inWork(GetNumber(1.0, 100000.0));
	ks1.CheckNumber_of_ceh();
	ks1.SetEfficiency();
	ks.push_back(ks1);                       //добавляем переменную в конец вектора
	ks[ks.size() - 1].SetID(ks.size());
}    

void PrintData(const vector<Pipe>& p,const vector<KS>& ks)   //Функция для вывода данных в консоль
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

void RedactPipe(vector<Pipe>& p)            //Функция для редактирования трубы
{
	if (p.size() == 0)
	{
		cout << "Нет доступных труб для редактирования" << endl;
	}
	else
	{
		cout << "Введите ID трубы, статус которой хотите редактировать (диапазон " << 1 << "-" << p.size() << ")" << endl;
		int id = GetNumber(1, p.size());
		p[id-1].ChangeStatus();
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
		int id = GetNumber(1, ks.size())-1;
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
				ks[id].SetName();
				break;
			case 2:
				cout << "Введите новое кол-во цехов КС:" << endl;
				ks[id].SetNumber_ceh(GetNumber(1,100000));
				ks[id].CheckNumber_of_ceh();
				ks[id].SetEfficiency();
				break;
			case 3:
				cout << "Введите новое кол-во работающих цехов КС:" << endl;
				ks[id].SetNumber_ceh_inWork(GetNumber(1.0, ks[id].GetNumber_ceh()));
				ks[id].CheckNumber_of_ceh();
				ks[id].SetEfficiency();
				break;
			case 0:
				break;
			}
		} while (WhatToRedact != 0);   //Выходим из цикла, когда пользователь введёт 0
	}
}

vector<int> FindPipe(const vector<Pipe>& p)
{
	cout << "Поиск труб по признаку 'в ремонте'\n" << endl;
	vector<int> res;
	int i;
	for (i = 0; i < p.size(); i++)
	{
		if (p[i].GetRemont())
			res.push_back(i);
	}
	return res;
}

vector<int> FindKS(const vector<KS>& ks)
{
	vector<int> res;
	cout << "1-Искать кс по названию" << endl << "2-Искать кс по проценту задействованных цехов" << endl;
	int what_to_find = GetNumber(1, 2);
	int i;
	if (what_to_find == 1)
	{
		cout << "Введите имя кс: ";
		string find_name;
		cin >> find_name;
		for (i = 0; i < ks.size(); i++)
		{
			if (ks[i].GetName()==find_name)
				res.push_back(i);
		}		
	}
	if (what_to_find == 2)
	{
		double procent;
		cout << "Введите желаемый процент задействованных цехов: ";
		procent = GetNumber(0.0, 100.0);
		for (i = 0; i < ks.size(); i++)
		{
			if (ks[i].GetEfficiency() > procent)
				res.push_back(i);
		}
	}
	return res;
}

void SaveData(const vector<Pipe>& p,const vector<KS>& ks)       //Описание функции сохранения
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
		for (i = 0; i < p.size(); i++)           //Выводим параметры каждой трубы по списку 
		{
			outf << p[i];
		}
		for (i = 0; i < ks.size(); i++)           //Выводим параметры каждой КС по списку 
		{
			outf << ks[i];
		}
		cout << "Данные успешно сохранены!" << endl;
	};
	outf.close();
}

void DownloadSaves(vector<Pipe>& p, vector<KS>& ks)         //Описание функции загрузки   
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
			for (i = 0; i < p.size(); i++)   //По порядку записываем данные в массив труб
				inf >> p[i];
			for (i = 0; i < ks.size(); i++)    //По порядку записываем данные в массив КС
				inf >> ks[i];
			cout << "Загрузка прошла успешно" << endl;
		}
	}
	inf.close();
}

void Menu()          //Функция вывода меню, выводит список возможных действий пользователя
{
	cout << "Меню программы" << endl <<
		"1-Добавить трубу" << endl <<
		"2-Добавить компрессорную станцию" << endl <<
		"3-Просмотр всех объектов" << endl <<
		"4-Редактировать трубу" << endl <<
		"5-Редактировать компрессорную станцию" << endl <<
		"6-Поиск труб по признаку 'в ремонте'" << endl <<
		"7-Поиск компрессорных станций" << endl <<
		"8-Сохранить в файл" << endl <<
		"9-Загрузить из файла" << endl <<
		"10-Открыть меню" << endl <<
		"0-Выход из программы" << endl;
}

int MakeStep()      // Функция, возвращающая число-действие, которое хочет совершить пользователь
{
	cout << "Какое действие вы хотите сделать?" << endl;
	int a = GetNumber(0, 10);
	return a;
}

int main()
{
	setlocale(LC_ALL, "Russian");              //Подключение русского языка
	vector <Pipe> pipes;                       //вектор для хранения труб
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
		    {
				vector<int> pipe_indexes = FindPipe(pipes);
				if (pipe_indexes.size() > 0)
				{
					int i;
					for (i = 0; i < pipe_indexes.size(); i++)
						cout << pipes[pipe_indexes[i]];
				}
				else 
					cout << "Труб в ремонте не найдено!" << endl;
		    }
			break;
		case 7:
		{
			vector<int> ks_indexes = FindKS(ks);
			if (ks_indexes.size() > 0)
			{
				int i;
				for (i = 0; i < ks_indexes.size(); i++)
					cout << ks[ks_indexes[i]];
			}
			else
				cout << "Компрессорных станций с данными параметрами не найдено!" << endl;
		}
		break;
		case 8:
			SaveData(pipes, ks);      //Сохранение данных в файл из массивов труб и КС
			break;
		case 9:
			DownloadSaves(pipes, ks);    //загрузка данных из файла
			break;
		case 10:                          //Показ меню
			Menu();
			break;
		case 0:
			return 0;
			break;
	    }
    }
}


