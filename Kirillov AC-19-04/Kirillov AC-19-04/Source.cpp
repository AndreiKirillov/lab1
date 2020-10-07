#include <iostream>
#include <fstream>
#include <string>
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
	float number_ceh;
	float number_ceh_inWork;
	float efficiency;
};

ofstream outf;       //Для вывода в файл
ifstream inf;        //Для загрузки из файла
int NumberPipe = 0;  //Переменная для количества труб
int NumberKS = 0;    //Переменная для кол-ва КС

pipe NewPipe()          //Функция создания новой трубы
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

KS NewKS()                  //Функция создания новой компрессорной станции
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
	int a;
	cin >> a;
	while (a < 0 || a > 8)
	{
		cout << "Введите верное число!" << endl;
		cin >> a;
	}
	return a;
}

bool ChangeStatus(bool b)   //Функция меняет статус переменной типа bool
{
	b = !b;
	return b;
}

void DownloadSaves(pipe p[100],KS k[100]);      //Объявление функции загрузки

void SaveData(pipe p[100], KS k[100]);          //Объявление функции сохранения

int main()
{
	setlocale(LC_ALL, "Russian");                                        //Подключение русского языка
	pipe pipes[100];                                                     //Массив для хранения труб
	KS ks[100];                                                          //Массив для хранения КС
	cout << "Вы хотите загрузить сохраненные данные? [y/n]" << endl;
	char ch;                                       
	cin >> ch;
	if (ch == 'y' || ch == '1')
		DownloadSaves(pipes, ks);            //спрашиваем у пользователя, хочет ли он загрузить данные после предыдущего запуска программы
	else if (ch == 'n' || ch == '0')
		cout << " " << endl;
	else
		cout << "Ошибка! Вы можете загрузить данные позже, напечатав '7'" << " " << endl;
	
	int i;
	Menu();                                  //показываем меню
	int operation = MakeStep();              //Запрашиваем действие пользователя
	while (operation != 0)                   //цикл закончится когда пользователь введёт 0
	{
		switch (operation)                   //цикл для обработки операций, выбранных пользователем
		{
		case 1:
			NumberPipe++;                   //увеличиваем счётчик труб
			pipes[NumberPipe] = NewPipe();  //записывааем в массив новую трубу
			pipes[NumberPipe].id = NumberPipe;   
			break;
		case 2:
			NumberKS++;                     //Тоже самое для КС
			ks[NumberKS] = NewKS();
			ks[NumberKS].id = NumberKS;
			break;
		case 3:                                  //Вывод списка объектов в консоль
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
		case 4:                                   //Редактируем статус "В ремонте" для трубы
			cout << "Введите ID трубы, статус которой хотите редактировать:" << endl;
			int b;
			cin >> b;
			while (b < 1 || b > NumberPipe)   //Проверка ввода
			{
				cout << "Такой трубы не существует! Введите верный ID" << endl;
				cin >> b;
			}
			pipes[b].remont = ChangeStatus(pipes[b].remont);   //Меняем статус
			break;
		case 5:                //Рекдактирование КС
			cout << "Введите ID компрессорной станции, которую хотите редактировать:" << endl;
			int a;
			cin >> a;
			while (a < 1 || a > NumberKS)
			{
				cout << "Такой трубы не существует! Введите верный ID" << endl;
				cin >> a;
			}
			cout << "Что именно вы хотите редактировать?" << endl;
			int WhatToRedact;  //Переменная, в неё запишется число, отражающее то что хочет редактировать пользователь
			do
			{
				cout << "1-редактировать имя" << endl << "2-редактировать кол-во цехов" << endl << "3-редактировать количество работающих цехов" << endl
					<< "0-закончить редактирование" << endl;   //Меню редактирования
				cin >> WhatToRedact;
				while (WhatToRedact < 0 || WhatToRedact>3)     //Проверяем корректность ввода
				{
					cout << "Такого действия не существует, введите корректное" << endl;
					cin >> WhatToRedact;
				}
				switch (WhatToRedact)   //редактируем нужный параметр, в зависимости от переменной
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

			} while (WhatToRedact != 0);   //Выходим из цикла, когда пользователь введёт 0
			break;
		case 6:
			SaveData(pipes, ks);      //Сохранение данных в файл из массивов труб и КС
			break;
		case 7:
			DownloadSaves(pipes, ks);    //загрузка данных из файла
			break;
		case 8:                          //Показ меню
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
		operation = MakeStep();   //В конце цикла просим снова ввести число
    }
	return 0;
}

void SaveData(pipe p[100], KS k[100])       //Описание функции сохранения
{
	int i;
	outf.open("Saves.txt");             
	if (NumberPipe == 0 && NumberKS == 0)   //Когда массивы данных труб и КС пусты, сохранения не произойдёт 
	{
		cout << "Нет данных для сохранения!" << endl;
	}
	else
	{
		outf << NumberPipe << endl;     //В первую строку выводим кол-во труб
		outf << NumberKS << endl;       //Во вторую кол-во КС
		i = 1;
		while (i <= NumberPipe)         //Выводим параметры каждой трубы по списку 
		{
			outf << p[i].id << endl;
			outf << p[i].length << endl;
			outf << p[i].diametr << endl;
			outf << p[i].remont << endl;
			i++;
		}
		i = 1;
		while (i <= NumberKS)           //Выводим параметры каждой КС по списку 
		{
			outf << k[i].id << endl;
			outf << k[i].name << endl;
			outf << k[i].number_ceh << endl;
			outf << k[i].number_ceh_inWork << endl;
			outf << k[i].efficiency << endl;
			i++;
		}
		cout << "Данные успешно сохранены!" << endl;
	};
	outf.close();
}

void DownloadSaves(pipe p[100], KS k[100])         //Описание функции загрузки   
{
	int i;
	inf.open("Saves.txt");
	inf >> NumberPipe;                       //Считываем количество труб в переменную
	inf >> NumberKS;                         //Теперь кол-во КС
	if (NumberPipe == 0 && NumberKS == 0)    //Если значения нулевые не загружаем данные 
	{
		cout << "Не удалось загрузить данные, файл пуст!" << endl;
	}
	else
	{
		i = 1;
		while (i <= NumberPipe)   //По порядку записываем данные в массив труб
		{
			inf >> p[i].id;
			inf >> p[i].length;
			inf >> p[i].diametr;
			inf >> p[i].remont;
			i++;
		}
		i = 1;
		while (i <= NumberKS)    //По порядку записываем данные в массив КС
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
