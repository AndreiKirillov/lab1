#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipe
{
	int id;
	int length;
	int diametr;
	bool remont;
};

struct KS
{
	int id;
	string name;
	float number_ceh;
	float number_ceh_inWork;
	float efficiency;
};

ifstream inf;
int NumberPipe = 0;
int NumberKS = 0;

pipe NewPipe()
{
	pipe pipe1;
	cout << "Введите длину трубы:";
	cin >> pipe1.length;
	cout << "Введите диаметр трубы:";
	cin >> pipe1.diametr;
	pipe1.id = 0;
	pipe1.remont = false;
	return pipe1;
}

KS NewKS()
{
	KS ks1;
	cout << "Введите имя компрессорной станции:";
	cin.ignore(32767, '\n');                                        //взял с https://ravesli.com/urok-57-vvedenie-v-std-string/
	getline(cin, ks1.name);
	cout << "Введите общее кол-во цехов и цехов в работе через пробел:";
	cin >> ks1.number_ceh >> ks1.number_ceh_inWork;
	ks1.efficiency = (ks1.number_ceh_inWork / ks1.number_ceh) * 100;
	return ks1;
}

int Menu()
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
		"0-Выход из программы" << endl<<
		"Что вы хотите сделать?"<<endl;
	int a;
	cin >> a;
	while (a < 0 || a > 8)
	{
		cout << "Введите верное число!" << endl;
		cin >> a;
	}
	return a;
}

int MakeStep()
{
	cout << "Какое действие вы хотите сделать?" << endl;
	int a;
	cin >> a;
	while (a < 0 || a > 8)
	{
		cout << "Введите верное число!" << endl;
		cin >> a;
	}
	return a;
}

bool ChangeStatus(bool b)
{
	b = !b;
	return b;
}

void DownloadSaves(pipe p[100],KS k[1]);

int main()
{
	setlocale(LC_ALL, "Russian");
	pipe pipes[100];
	KS ks[100];
	cout << "Вы хотите загрузить сохраненные данные? [y/n]" << endl;
	char ch;
	cin >> ch;
	if (ch == 'y' || ch == '1')
		DownloadSaves(pipes, ks);
	else if (ch = 'n' || ch == '0')
		cout << " " << endl;
	else
		cout << "Ошибка! Вы можете загрузить данные позже, напечатав '7'" << " " << endl;
	
	int i;
	ofstream outf;
	int operation = Menu();
	while (operation != 0)
	{
		switch (operation)
		{
		case 1:
			NumberPipe++;
			pipes[NumberPipe] = NewPipe();
			pipes[NumberPipe].id = NumberPipe;
			break;
		case 2:
			NumberKS++;
			ks[NumberKS] = NewKS();
			ks[NumberKS].id = NumberKS;
			break;
		case 3:
			cout << "Список труб:" << endl;
			if (NumberPipe == 0)
			{
				cout << "Список труб пуст" << endl << " " << endl;
			}
			else
			{
				for (i = 1; i < NumberPipe + 1; i++)
				{
					cout << "ID трубы:" << pipes[i].id << endl;
					cout << "Длинна трубы:" << pipes[i].length << endl;
					cout << "Диаметр трубы:" << pipes[i].diametr << endl;
					cout << "Статус ремонта:" << pipes[i].remont << endl << " " << endl;
				}
			}
			cout << "Список компрессорных станций:" << endl;
			if (NumberKS == 0)
			{
				cout << "Список компрессорных станций пуст" << endl << " " << endl;
			}
			else
			{
				for (i = 1; i < NumberKS + 1; i++)
				{
					cout << "ID КС:" << ks[i].id << endl;
					cout << "Имя КС:" << ks[i].name << endl;
					cout << "Работающие цеха:" << ks[i].number_ceh_inWork << "/" << ks[i].number_ceh << endl;
					cout << "Эффективность компрессорной станции" << ks[i].efficiency << "%" << endl << " " << endl;
				}
			}
			break;
		case 4:
			cout << "Введите ID трубы, статус которой хотите редактировать:" << endl;
			int b;
			cin >> b;
			while (b < 1 || b > NumberPipe)
			{
				cout << "Такой трубы не существует! Введите верный ID" << endl;
				cin >> b;
			}
			pipes[b].remont = ChangeStatus(pipes[b].remont);
			break;
		case 5:
			cout << "Введите ID компрессорной станции, которую хотите редактировать:" << endl;
			int a;
			cin >> a;
			while (a < 1 || a > NumberKS)
			{
				cout << "Такой трубы не существует! Введите верный ID" << endl;
				cin >> a;
			}
			cout << "Что именно вы хотите редактировать?" << endl;
			int WhatToRedact;
			do
			{
				cout << "1-редактировать имя" << endl << "2-редактировать кол-во цехов" << endl << "3-редактировать количество работающих цехов" << endl
					<< "0-закончить редактирование" << endl;
				cin >> WhatToRedact;
				while (WhatToRedact < 0 || WhatToRedact>3)
				{
					cout << "Такого действия не существует, введите корректное" << endl;
					cin >> WhatToRedact;
				}
				switch (WhatToRedact)
				{
				case 1:
					cout << "Введите новое имя КС:" << endl;
					cin >> ks[a].name;
					break;
				case 2:
					cout << "Введите новое кол-во цехов КС:" << endl;
					cin >> ks[a].number_ceh;
					ks[a].efficiency = (ks[a].number_ceh_inWork / ks[a].number_ceh) * 100;
					break;
				case 3:
					cout << "Введите новое кол-во работающих цехов КС:" << endl;
					cin >> ks[a].number_ceh_inWork;
					ks[a].efficiency = (ks[a].number_ceh_inWork / ks[a].number_ceh) * 100;
					break;
				case 0:
					break;
				}

			} while (WhatToRedact != 0);
			break;
		case 6:
			outf.open("Saves.txt");
			if (NumberPipe == 0 && NumberKS == 0)
			{
				cout << "Нет данных для сохранения!" << endl;
			}
			else
			{
				outf << NumberPipe << endl;
				outf << NumberKS << endl;
				i = 1;
				while (i <= NumberPipe)
				{
					outf << pipes[i].id << endl;
					outf << pipes[i].length << endl;
					outf << pipes[i].diametr << endl;
					outf << pipes[i].remont << endl;
					i++;
				}
				i = 1;
				while (i <= NumberKS)
				{
					outf << ks[i].id << endl;
					outf << ks[i].name << endl;
					outf << ks[i].number_ceh << endl;
					outf << ks[i].number_ceh_inWork << endl;
					outf << ks[i].efficiency << endl;
					i++;
				}
			};
			outf.close();
			cout << "Данные успешно сохранены!" << endl;
			break;
		case 7:
			DownloadSaves(pipes, ks);
			break;
		case 8:
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
			break;
	
	    }
		operation = MakeStep();
    }
	return 0;
}

void DownloadSaves(pipe p[100], KS k[100])
{
	int i;
	inf.open("Saves.txt");
	inf >> NumberPipe;
	inf >> NumberKS;
	if (NumberPipe == 0 && NumberKS == 0)
	{
		cout << "Не удалось загрузить данные, файл пуст!" << endl;
	}
	else
	{
		i = 1;
		while (i <= NumberPipe)
		{
			inf >> p[i].id;
			inf >> p[i].length;
			inf >> p[i].diametr;
			inf >> p[i].remont;
			i++;
		}
		i = 1;
		while (i <= NumberKS)
		{
			inf >> k[i].id;
			inf >> k[i].name;
			inf >> k[i].number_ceh;
			inf >> k[i].number_ceh_inWork;
			inf >> k[i].efficiency;
			i++;
		}
	}
	inf.close();
	cout << "Загрузка прошла успешно" << endl;
}
