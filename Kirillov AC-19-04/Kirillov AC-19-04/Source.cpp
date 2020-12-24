#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Pipe.h"
#include "KS.h"
#include "Source.h"
#include "Graph.h"
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
	p1.length=GetNumber(1, 10000000);
	cout << "Введите диаметр трубы:";
	p1.diametr=GetNumber(1, 10000000);
	p.push_back(p1);               //Добавляем в конец вектора труб
	//p[p.size() - 1].id=p.size();

}

void NewKS(vector<KS>& ks)                  //Функция создания новой компрессорной станции
{
	KS ks1;
	ks1.SetName();
	cout << "Введите общее кол-во цехов:";
	ks1.SetNumber_ceh(GetNumber(1.0, 100000.0));
	cout << "Введите кол-во цехов в работе:";
	ks1.SetNumber_ceh_inWork(GetNumber(0.0, 100000.0));
	ks1.efficiency= (ks1.number_ceh_inWork / ks1.number_ceh) * 100;
	ks.push_back(ks1);                       //добавляем переменную в конец вектора
	//ks[ks.size() - 1].id=ks.size();
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

vector<int> FindPipe(const vector<Pipe>& p, int MaxPossibleValue);   //Объявление чтобы использовать функцию

void RedactPipe(vector<Pipe>& p)            //Функция для редактирования трубы
{
	if (p.size() == 0)
	{
		cout << "Нет доступных труб для редактирования" << endl;
	}
	else
	{
	    vector<int> pipe_indexes = FindPipe(p, p.size());             //Меняем статус найденных труб
		for (int i = 0; i < pipe_indexes.size(); i++)
		{
			p[pipe_indexes[i]].ChangeStatus();
		}
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
		cout << "Введите ID компрессорной станции, которую хотите редактировать(диапазон " << 1 << "-" << ks[0].MAX_ID << ")" << endl;
		int id = GetNumber(1, ks[0].MAX_ID);
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
				ks[id].SetNumber_ceh(GetNumber(ks[id].number_ceh_inWork, 100000));
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;;
				break;
			case 3:
				cout << "Введите новое кол-во работающих цехов КС:" << endl;
				ks[id].SetNumber_ceh_inWork(GetNumber(1.0, 100000.0));
				ks[id].efficiency = (ks[id].number_ceh_inWork / ks[id].number_ceh) * 100;;
				break;
			case 0:
				break;
			}
		} while (WhatToRedact != 0);   //Выходим из цикла, когда пользователь введёт 0
	}
}

vector<int> FindPipe(const vector<Pipe>& p, int MaxPossibleValue)        //Функция нахождения труб
{
	vector<int> res;
	if (MaxPossibleValue > 1)
	{
		cout << "1 - трубы в ремонте" << endl <<
			"2 - трубы без ремонта" << endl <<
			"3 - выбрать конкретные трубы" << endl;
		int what_to_find = GetNumber(1, 3);
		int i;
		if (what_to_find == 1)
		{
			for (i = 0; i < p.size(); i++)
			{
				if (p[i].remont)      //Трубы в ремонте
					res.push_back(i);
			}
		}
		if (what_to_find == 2)
		{
			for (i = 0; i < p.size(); i++)
			{
				if (!p[i].remont)        //Трубы без ремонта
					res.push_back(i);
			}
		}
		if (what_to_find == 3)
		{
			if (p.size() != 0)
			{
				cout << "Вводите ID труб, которые хотите найти (диапазон " << 1 << "-" << p.size() << ")" << endl <<
					"Чтобы закончить, введите ноль" << endl;
				int id;
				do
				{                                                 //Ищем трубы по желанию пользователя
					id = GetNumber(0, p.size());
					if (id != 0)
						res.push_back(id - 1);
				} while (id != 0);
			}
		}
		if (res.size() == 0)
			cout << "Труб по данным параметрам не найдено!" << endl;
		return res;
	}
	else
	{
		if (p.size() > 0)
		{
			cout << "Можно выбрать только одну трубу!" << endl;
			cout << "Введите ID трубы, которую хотите выбрать (диапазон " << 1 << "-" << p[0].MAX_ID << ")" << endl;
			int pipe_id = GetNumber(1, p[0].MAX_ID);
			for (int i = 0; i < p.size(); i++)
				if (p[i].id == pipe_id)
					res.push_back(i);
			return res;
		}
		else
		{
			res.push_back(-1);
			cout << "Труб не существует!" << endl;
			return res;
		}
	}
	
}

template<typename T>                                  //Шаблон
using Filter = bool(*)(const KS&, T parametr);        //Указатель на функцию 

bool CheckByID(const KS& ks, int parametr)
{
	return ks.id == parametr;
}

bool CheckByName(const KS& ks, string parametr)        //Функция для поиска по имени
{
	return ks.name == parametr;
}

bool CheckByProcent(const KS& ks, double parametr)       //Функция для поиска по задействованным цехам
{
	return ks.efficiency >= parametr;
}

template<typename T>
vector<int> FindKS(const vector<KS>& ks, Filter<T> f, T parametr)         //Функция нахождения кс
{
	vector<int> res;                         //Вектор для хранения индексов
	int i;
	for (i = 0; i < ks.size(); i++)
	{
		if (f(ks[i], parametr))            //Проверяем совпадение с помощью указателя
			res.push_back(i);
	}		
	return res;
}

vector<int> UserChooseKS(const vector<KS>& ks, int MaxPossibleValue)
{
	vector<int> ks_indexes;                                              //Вектор, хранящий индексы найденных кс
	cout << "1-Искать кс по ID" << endl << "2-Искать кс по названию" << endl << "3-Искать кс по проценту задействованных цехов" << endl;
    int what_to_find = GetNumber(1, 3);
	if (what_to_find == 1)
	{
		if (ks.size() != 0)
		{
			cout << "Вводите ID кс, которые хотите найти (диапазон " << 1 << "-" << ks[0].MAX_ID << ")" << endl <<
				"Чтобы закончить, введите ноль" << endl;
			int id;
			do
			{                                                 //Ищем кс по желанию пользователя
				id = GetNumber(0, ks[0].MAX_ID);
				if (id != 0)
				{
					for(int i=0;i<ks.size();i++)
						if(ks[i].id==id)
							ks_indexes.push_back(i);
				}
			} while (id != 0 && ks_indexes.size()<MaxPossibleValue);
		}
	}else
	if (what_to_find == 2)
	{
		cout << "Введите имя кс: ";
		string find_name;
		cin >> find_name;
		ks_indexes = FindKS<string>(ks, CheckByName, find_name);
	}else
	if (what_to_find == 3 && MaxPossibleValue>1)
	{
		double procent;
		cout << "Введите желаемый процент задействованных цехов: ";
		procent = GetNumber(0.0, 100.0);
		ks_indexes = FindKS(ks, CheckByProcent, procent);
	}else
	{
		cout << "Нельзя искать по проценту задействанных цехов!" << endl;
	}
	if (MaxPossibleValue > 1)
		return ks_indexes;
	else
	{
		if(ks_indexes.size()==0)
		ks_indexes.push_back(-1);
		return ks_indexes;
	}
}

void DeletePipes(vector<Pipe>& p, Graph& g)        //Удаление труб
{
	vector<int> pipe_indexes = FindPipe(p,p.size());
	for (int i = 0; i < p.size(); i++)
	{
		for (int j = 0; j < pipe_indexes.size(); j++)
		{
			if (p[i].id == p[pipe_indexes[j]].id)
			{
				
				if (g.Pipes_in_Graph.find(p[pipe_indexes[j]].id) != g.Pipes_in_Graph.end())
					g.Pipes_in_Graph.erase(p[pipe_indexes[j]].id);
				int value = 0;
				for (int k = 0; k < g.All_edges.size(); k++)
					if (g.All_edges[k].cost == p[pipe_indexes[j]].length)   //Удаляем нужное ребро из массива всех рёбер   
						g.All_edges.erase(g.All_edges.begin() + k);
				p.erase(p.begin() + i);
			}
		}
	}
}

void DeleteKS(vector<KS>& ks, vector<Pipe>& p, Graph& g)      //Удаление кс
{
	vector<int> ks_indexes = UserChooseKS(ks, ks.size());
	for (int i = 0; i < ks.size(); i++)
	{
		for (int j = 0; j < ks_indexes.size(); j++)
		{
			if (ks[i].id == ks[ks_indexes[j]].id)           
			{
				for (int k = 0; k < g.ReNumbered_ks.size(); k++)
					if (g.ReNumbered_ks[k] == ks[ks_indexes[j]].id)    //Корректируем порядковые номера кс
					{
						for (int n = k + 1; n < g.ReNumbered_ks.size(); n++)  //для тех номеров, что идут после
							for (auto& edge : g.All_edges)
							{
								if (g.ReNumbered_ks[edge.a] == g.ReNumbered_ks[n])
									edge.a--;
								if (g.ReNumbered_ks[edge.b] == g.ReNumbered_ks[n])
									edge.b--;
							}
						g.ReNumbered_ks.erase(g.ReNumbered_ks.begin() + k);
						break;
					}
				for (auto& pipe : p)              //Если кс задействована в сети, то надо удалить связи труб с ней
					if (pipe.input == ks[i].id || pipe.output == ks[i].id)
					{
						pipe.input = 0;
						pipe.output = 0;
						g.Pipes_in_Graph.erase(pipe.id);              //Удаляем трубу
						for (int k = 0; k < g.All_edges.size(); k++)
							if (pipe.length == g.All_edges[k].cost)
								g.All_edges.erase(g.All_edges.begin() + k);    //Удаляем ребро графа
					}                                                        //Может остаться одинокая кс в сети, пока не рассмотрел этот случай
				if (g.KS_in_Graph.find(ks[i].id) != g.KS_in_Graph.end())
					g.KS_in_Graph.erase(ks[i].id);
				ks.erase(ks.begin() + i);
			}
		}
	}
}

void SaveData(const vector<Pipe>& p,const vector<KS>& ks, const Graph& g)       //Описание функции сохранения
{
	cout << "Введите название файла для сохранения" << endl;
	string filename;
	cin >> filename;
	filename += ".txt";
	ofstream outf;
	int i;
	outf.open(filename);
	if (p.size() == 0 && ks.size() == 0)   //Когда массивы данных труб и КС пусты, сохранения не произойдёт 
	{
		cout << "Нет данных для сохранения!" << endl;
	}
	else if (outf.is_open())
	{
		outf << p.size() << endl;     //В первую строку выводим кол-во труб
		outf << ks.size() << endl;    //Во вторую кол-во КС 
		outf << g.Pipes_in_Graph.size() << endl;  //Сохраним основные параметры сети
		outf << g.KS_in_Graph.size() << endl;
		outf << g.ReNumbered_ks.size() << endl;
		outf << g.All_edges.size() << endl;
		for (i = 0; i < p.size(); i++)           //Выводим параметры каждой трубы по списку 
		{
			outf << p[i];
		}
		for (i = 0; i < ks.size(); i++)           //Выводим параметры каждой КС по списку 
		{
			outf << ks[i];
		}
		outf << g << endl;
		cout << "Данные успешно сохранены!" << endl;
	};
	outf.close();
}

void DownloadSaves(vector<Pipe>& p, vector<KS>& ks, Graph& g)         //Описание функции загрузки   
{
	cout << "Введите название файла для загрузки" << endl;
	string filename;
	cin >> filename;
	filename += ".txt";
	ifstream inf;
	int i=0;
	int SizePipes, SizeKS, SizePipes_in_Graph, SizeKS_in_Graph, SizeRenumberedKS, SizeAll_edges;
	inf.open(filename);
	if (inf.is_open())
	{
		inf >> SizePipes;                       //Считываем количество труб в переменную
		inf >> SizeKS;                         //Теперь кол-во КС
		inf >> SizePipes_in_Graph;
		inf >> SizeKS_in_Graph;
		inf >> SizeRenumberedKS;
		inf >> SizeAll_edges;
		if (SizePipes == 0 && SizeKS == 0)    //Если значения нулевые не загружаем данные 
		{
			cout << "Не удалось загрузить данные, файл пуст!" << endl;
		}
		else
		{
			int data;
			p.resize(SizePipes);
			ks.resize(SizeKS);
			g.ReNumbered_ks.resize(SizeRenumberedKS);
			g.All_edges.resize(SizeAll_edges);
			for (i = 0; i < p.size(); i++)   //По порядку записываем данные в массив труб
				inf >> p[i];
			for (i = 0; i < ks.size(); i++)    //По порядку записываем данные в массив КС
				inf >> ks[i];
			for (i = 0; i < SizePipes_in_Graph;i++)
			{
				inf >> data;
				g.Pipes_in_Graph.insert(data);
			}
			for (i = 0; i < SizeKS_in_Graph; i++)
			{
				inf >> data;
				g.KS_in_Graph.insert(data);
			}
			for (i = 0; i < g.ReNumbered_ks.size(); i++)
				inf >> g.ReNumbered_ks[i];
			for (i = 0; i < g.All_edges.size(); i++)
			{
				inf >> g.All_edges[i].a;
				inf >> g.All_edges[i].b;
				inf >> g.All_edges[i].cost;
			}
			cout << "Загрузка прошла успешно" << endl;
		}
	}
	else
		cout << "Не удалось произвести загрузку, введите корректное имя файла!" << endl;
	inf.close();
}

map<int,int> UserChooseGraphKS(Graph& g )      //Функция, где пользователь выбирает начальную и конечную вершины графа
{
	map<int, int> Result;
	set<int> possible_start;     //Возможные начальные вершины
	set<int> possible_end;        //Конечные
	cout << "Выберите начальную кс, доступны: ";   //выбирает начало
	int beginning;
	for (int i = 0; i < g.Matrix.size(); i++)
		if (g.CheckLine(i, "line"))
		{
			cout << g.ReNumbered_ks[i]<<" ";
			possible_start.insert(g.ReNumbered_ks[i]);
		}
	while ((cin >> beginning).fail() || possible_start.find(beginning) == possible_start.end()) //Проверяем ввод на допустимость
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Введите корректное число!" << endl;
	}
	cout << "Выберите конечную кс, доступны: ";// выбирает конец
	int end;
	for (int i = 0; i < g.Matrix.size(); i++)
		if (g.CheckLine(i, "column"))
		{
			cout << g.ReNumbered_ks[i]<<" ";
			possible_end.insert(g.ReNumbered_ks[i]);
		}
	while ((cin >> end).fail() || possible_end.find(end) == possible_end.end()) //Проверяем ввод на допустимость
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Введите корректное число!" << endl;
	}
	Result.emplace(g.ConvertKS(beginning), g.ConvertKS(end));
	return Result;
}

void Menu()          //Функция вывода меню, выводит список возможных действий пользователя
{
	cout << "Меню программы" << endl <<
		"1-Добавить трубу" << endl <<
		"2-Добавить компрессорную станцию" << endl <<
		"3-Соединить компрессорные станции" << endl <<
		"4-Просмотр всех объектов" << endl <<
		//"5-Редактировать трубу" << endl <<
		//"6-Редактировать компрессорную станцию" << endl <<
		//"7-Поиск труб по признаку 'в ремонте'" << endl <<
		//"8-Поиск компрессорных станций" << endl <<
		"9-Удалить объекты" << endl <<
		"10-Просмотр газотранспортной сети" << endl <<
		"11-Топологическая сортировка" << endl <<
		"12-Найти кратчайший путь" << endl <<
		"13-Расчёт максимального потока сети" << endl <<
		"14-Сохранить в файл" << endl <<
		"15-Загрузить из файла" << endl <<
		"16-Открыть меню" << endl <<
		"0-Выход из программы" << endl;
}

int MakeStep()      // Функция, возвращающая число-действие, которое хочет совершить пользователь
{
	cout << "Какое действие вы хотите сделать?" << endl;
	int a = GetNumber(0, 16);
	return a;
}

int main()
{
	setlocale(LC_ALL, "Russian");          //Подключение русского языка
	vector <Pipe> pipes;                       //вектор для хранения труб
	vector <KS> ks;                            //вектор для хранения КС
	Graph GasNetwork;
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
		case 3:
			GasNetwork.ConnectKSbyPipe(pipes, ks);
			break;
		case 4:                                  //Вывод списка объектов в консоль
			PrintData(pipes, ks);
			break;
		case 5:                                   //Редактируем статус "В ремонте" для трубы
			RedactPipe(pipes);
			break;
		case 6:                //Рекдактирование КС
			RedactKS(ks);
			break;
		case 7:
		    {
			cout << "Поиск труб " << endl;
				vector<int> pipe_indexes = FindPipe(pipes,pipes.size());       //Вектор, хранящий индексы найденных труб
				if (pipe_indexes.size() > 0)                      
				{
					int i;
					for (i = 0; i < pipe_indexes.size(); i++)
						cout << pipes[pipe_indexes[i]];            //Выводим найденные трубы
				}
		    }
			break;
		case 8:
		{
			vector<int> ks_indexes = UserChooseKS(ks,ks.size());                                            //Вектор, хранящий индексы найденных кс
			if (ks_indexes.size() > 0)
			{
				cout << "Найденные компрессорные станции:" << endl;
				int i; 
				for (i = 0; i < ks_indexes.size(); i++)
					cout << ks[ks_indexes[i]];
			}
			else
				cout << "Компрессорных станций с данными параметрами не найдено!" << endl;
		}
		break;
		case 9:
		{
			cout << "Что вы хотите удалить?" << endl << "1-Трубы" << endl << "2-КС" << endl;
			int WhatToDelete = GetNumber(1, 2);
			if (WhatToDelete == 1)
			{
				DeletePipes(pipes,GasNetwork);
			}
			else
			{
				DeleteKS(ks, pipes, GasNetwork);
			}
		}
		break;
		case 10:
		{
			GasNetwork.PrintGraph();
		}
		break;
		case 11:
		{
			GasNetwork.TopologicalSort();
		}
		break;
		case 12:
		{
			GasNetwork.CreateGraph();
			if (GasNetwork.EmptyGraph)
				cout << "Ошибка! Отсутствует газотранспортная сеть!" << endl;
			else
			{
				GasNetwork.PrintGraph();             //Показываем пользователю сеть
				map<int, int> peaks = UserChooseGraphKS(GasNetwork);
				auto it = peaks.begin();
				if (it->first != it->second)
				{
					int Length = GasNetwork.ShortestWay(it->first, it->second);
					if (Length == 100000000)
						cout << "Между данными компрессорными станциями нет пути!" << endl;
					else
						cout << "Кратчайший путь между вершинами равен " << Length << endl << endl;
				}
				else
					cout << "Начальная и конечная вершина совпадают, попробуйте снова!" << endl;
			}
		}
		break;
		case 13:
		{
			GasNetwork.CreateGraph();
			if (GasNetwork.EmptyGraph)
				cout << "Ошибка! Отсутствует газотранспортная сеть!" << endl;
			else
			{
				map<int, int> peaks = UserChooseGraphKS(GasNetwork);
				auto it = peaks.begin();
				if (it->first != it->second)
				{
					int Flow = GasNetwork.MaxFlow(it->first, it->second);
					if (Flow == 0)
						cout << "Между данными компрессорными станциями не существует потока!" << endl;
					else
						cout << "Максимальный поток между данными вершинами равен " << Flow << endl;
				}
				else
					cout << "Начальная и конечная вершина совпадают, попробуйте снова!" << endl;
				
			}
		}
		break;
		case 14:
			SaveData(pipes, ks, GasNetwork);      //Сохранение данных в файл из массивов труб и КС
			break;
		case 15:
			DownloadSaves(pipes, ks, GasNetwork);    //загрузка данных из файла
			break;
		case 16:                          //Показ меню
			Menu();
			break;
		case 0:
			return 0;
			break;
	    }
    }
}


