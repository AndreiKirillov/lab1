#include <iostream>
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
	while (a < 0 || a > 7)
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
	while (a < 0 || a > 7)
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

int main()
{
	setlocale(LC_ALL, "Russian");
	pipe pipes[100];
	KS ks[100];
	int NumberPipe = 0;
	int NumberKS = 0;
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
		    	cout << "Список труб пуст" << endl;
	    	}
	    	else
	    	{
	    		int i;
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
	    		cout << "Список компрессорных станций пуст" << endl;
	    	}
	    	else
	    	{
	    		int j;
	    		for (j = 1; j < NumberKS + 1; j++)
	    		{
	    			cout << "ID КС:" << ks[j].id << endl;
	    			cout << "Имя КС:" << ks[j].name << endl;
	    			cout << "Работающие цеха:" << ks[j].number_ceh_inWork << "/" << ks[j].number_ceh << endl;
	    			cout << "Эффективность компрессорной станции" << ks[j].efficiency << "%" << endl << " " << endl;
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
	    }
		operation = MakeStep();
    }
	return 0;
}
