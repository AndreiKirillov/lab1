#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct pipe      //Описание структуры трубы
{
	int id;
	int length;
	int diametr;
	bool remont;
};

struct KS                //Описание структуры компрессорной станции
{
	int id;
	string name;
	double number_ceh;
	double number_ceh_inWork;
	double efficiency;
};

template <typename T>
T GetNumber(T min, T max)
{
	T a;
	cin.clear();
	cin.ignore(33333, '\n');
	cin >> a;
	while (cin.fail() || a < min || a > max)
	{
		cin.clear();
		cin.ignore(33333, '\n');
		cout << "Введите корректное число!" << endl;
		cin >> a;
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
	p.push_back(p1);
	p[p.size() - 1].id = p.size();
}

void NewKS(vector<KS>& ks)                  //Функция создания новой компрессорной станции
{
	KS ks1;
	cout << "Введите имя компрессорной станции:";
	cin.ignore(32767, '\n');                                       
	getline(cin, ks1.name);
	cout << "Введите общее кол-во цехов и цехов в работе через пробел:";
	do
	{
		ks1.number_ceh = GetNumber(1.0, 100000.0);
		ks1.number_ceh_inWork = GetNumber(1.0, 100000.0);
		if (ks1.number_ceh < ks1.number_ceh_inWork)
		{
			cout << "Введите корректные данные!" << endl;
		}
	} while (ks1.number_ceh <= ks1.number_ceh_inWork);
	ks1.efficiency = (ks1.number_ceh_inWork / ks1.number_ceh) * 100;
	ks1.id = 0;
	ks.push_back(ks1);
	ks[ks.size() - 1].id = ks.size();
}    

ostream& operator <<(ostream& out, pipe& p)
{
	out << "ID трубы:" << p.id << endl;
	out << "Длинна трубы:" << p.length << endl;
	out << "Диаметр трубы:" << p.diametr << endl;
	out << "Статус ремонта:" << p.remont << endl << " " << endl;
	return out;
}

ostream& operator <<(ostream& out, KS& ks)
{
	out << "ID КС:" << ks.id << endl;
	out << "Имя КС:" << ks.name << endl;
	out << "Работающие цеха:" << ks.number_ceh_inWork << "/" << ks.number_ceh << endl;
	out << "Эффективность компрессорной станции" << ks.efficiency << "%" << endl << " " << endl;
	return out;
}

void PrintData(vector<pipe> p,vector<KS> ks)
{
	int i;
	cout << "Список труб:" << endl;
	if (p.size() == 0)
	{
		cout << "Список труб пуст" << endl << " " << endl;
	}
	else
	{
		for (i = 0; i < p.size(); i++)
		{
			cout << p[i] << endl;
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

void RedactPipe(vector<pipe>& p)
{
	if (p.size() == 0)
	{
		cout << "Нет доступных труб для редактирования" << endl;
	}
	else
	{
		cout << "Введите ID трубы, статус которой хотите редактировать (диапазон " << 1 << "-" << p.size() << ")" << endl;
		int b = p.size();
		int id = GetNumber(1, b);
		ChangeStatus(p[id-1].remont);
	}
}

void RedactKS(vector<KS>& ks)
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
			cout << "1-редактировать имя" << endl << "2-редактировать кол-во цехов" << endl << "3-редактировать количество работающих цехов" << endl
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

void SaveData(vector<pipe> p, vector<KS> ks)       //Описание функции сохранения
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
		outf << ks.size() << endl;
		if (p.size() > 0)                                     //Во вторую кол-во КС
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
	setlocale(LC_ALL, "Russian");                                        //Подключение русского языка
	vector <pipe> pipes;                                                     //Массив для хранения труб
	vector <KS> ks;                                                          //Массив для хранения КС
	cout << "Вы хотите загрузить сохраненные данные? [y/n]" << endl;
	char ch;                                       
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
		DownloadSaves(pipes, ks);            //спрашиваем у пользователя, хочет ли он загрузить данные после предыдущего запуска программы
	else if (ch == 'n' || ch == 'N')
		cout << " " << endl;
	else
		cout << "Ошибка! Вы можете загрузить данные позже, напечатав '7'" << " " << endl;
	Menu();                                  //показываем меню
	int operation = MakeStep();              //Запрашиваем действие пользователя
	while (1)                   //цикл закончится когда пользователь введёт 0
	{
		switch (operation)                   //цикл для обработки операций, выбранных пользователем
		{
		case 1:                  
			NewPipe(pipes);  //записывааем в массив новую трубу   
			break;
		case 2:
			NewKS(ks);
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
		operation = MakeStep();   //В конце цикла просим снова ввести число
    }
}


