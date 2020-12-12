#include "Graph.h"
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include <vector>
#include<set>

void Graph::ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks)             //Функция добавления связи между кс
{
	if (p.size() == 0 || ks.size() < 2 || (p.size() == 0 && ks.size() < 2))    //Проверяем достаточно ли объектов
	{
		cout << "Невозможно соединить КС, так как недостаточно объектов" << endl;
	}
	else
	{
		bool PotentialError = false;
		cout << "Выберите начальную компрессорную станцию:" << endl;            // Пользователь выбирает нужные объекты
		vector<int> begin = UserChooseKS(ks, 1);
		int a = begin[0];
		cout << "Выберите конечную компрессорную станцию:" << endl;            //////Сделать потом чтоб не заставлять выбирать если ошибка
		vector<int> end = UserChooseKS(ks, 1);
		int b = end[0];                                                             // а, b, pipe - индекс
		cout << "Выберите трубу для соединения компрессорных станций:" << endl;
		vector<int> v = FindPipe(p, 1);
		int pipe = v[0];   
		if (p[pipe].remont == true || Pipes_in_Graph.find(pipe + 1) != Pipes_in_Graph.end())
		{
			PotentialError = true;            //Труба не должна быть в ремонте или уже быть использованной в сети
			cout << "Нельзя использовать данную трубу!" << endl;
		}
		if (a >= 0 && b >= 0 && a != b && pipe >= 0 && !PotentialError)       //Если всё нормально
		{
			p[pipe].input = a + 1;       //Храним id
			p[pipe].output = b + 1;
			Pipes_in_Graph.insert(pipe + 1);
			KS_in_Graph.insert(a + 1);
			KS_in_Graph.insert(b + 1);
		}
		else
		{
			cout << "Ошибка! Попробуйте заново!" << endl;
			if (a == b)
				cout << "Необходимо указывать разные компрессорные станции!" << endl;
		}
	}
}

void Graph::CreateGraph(const vector<Pipe>& p, const vector<KS>& ks)   //Функция создания матрицы смежности
{
	vector<vector<int>> matrix(ks.size(), vector<int>(ks.size()));      //Создаем матрицу исходя из кол-ва кс в базе
	for (int i = 0; i < ks.size(); i++)
		for (int j = 0; j < ks.size(); j++)
			matrix[i][j] = 0;                         //Зануляем все элементы
	for (auto &pipe_id : Pipes_in_Graph)         //Проходимся по трубам, задействованным в графе
	{
		matrix[p[pipe_id-1].input - 1][p[pipe_id-1].output - 1] = 1;      //Добавляем связь
	}
	Matrix = matrix;         //Присваиваем готовую матрицу полю класса
}

void Graph::PrintGraph()        //Функция вывода графа в консоль
{
	//Выводим список смежности
	bool Matrix_is_empty = false;
	if (Pipes_in_Graph.size() == 0) 
		Matrix_is_empty = true;
	if (!Matrix_is_empty)        //Выводим граф только, если матрица не пустая
	{
		cout << "\tГазотранспортная сеть\t\n\n" <<
			"Компрессорная станция <---> смежные с ней станции" << endl << endl;
		for (int i = 0; i < Matrix.size(); i++)
		{
			bool endline = false;                      //Переменная чтобы знать, нужно ли переводить строку
			for (int j = 0; j < Matrix[i].size(); j++)
				if (Matrix[i][j] == 1)
				{
					if (endline == false)
					{
						cout << i+1 << "\t-\t" << j+1;       //Выводим id
						endline = true;
					}
					else
						cout << ", " << j;
				}
			if (endline)
				cout << endl;
		}
		cout << endl;
	}
	else
		cout << "Газотранспортной сети не существует, так как нет связей между компрессорными станциями" << endl;
}

void Graph::TopologicalSort()       //Функция топологической сортировки
{
	map<int, int> SortedKS;     //ключ - номер вершины, значение - id КС
	int NumberOfKS = KS_in_Graph.size();           //Неиспользованные вершины
	vector<vector<int>> Matrix_Copy = Matrix;      //Копия матрицы смежности, чтобы занулять строки
	set<int> CopyKS = KS_in_Graph;               //Копия вершин графа, чтобы удалять их
	do//Пока есть неиспользованные вершины
	{
		skip:                     //Лейбл для goto
		for (int ks : CopyKS)      //Перебираем неиспользованные вершины
		{
			bool VoidLine = true;         //Если строка только с 0
			bool DeletedElement = false;  //Если удалили вершину
			for (int j = 0; j < Matrix_Copy[ks-1].size(); j++)   //Проверяем строку на занулённость
			{
				if (Matrix_Copy[ks-1][j] == 1)         
					VoidLine = false;
			}
			if (VoidLine == true)    //Если строка из нулей
			{
				SortedKS.emplace(NumberOfKS, ks); //Добавляем вершину в список отсортированных
				NumberOfKS--;                     //Уменьшаем
				for (int i = 0; i < Matrix_Copy.size(); i++)
					Matrix_Copy[i][ks - 1] = 0;               //Зануляем элементы использованной вершины
				CopyKS.erase(ks);                 //Помечаем вершину как использованную
				DeletedElement = true;  
			}
			if (DeletedElement)       //Если удалили вершину, начинаем цикл заново
				goto skip;         
		}
	} while (NumberOfKS > 0);     
	////Выводим результат
	cout << "\tТопографическая сортировка\t\n\n";
	cout << "№ КС - id КС" << endl << endl;
	for(auto& n :SortedKS)
	{
		cout << n.first << "\t" << n.second << endl;
	}
	//return map<int, int>();
}

//bool Graph::CheckCycle()
//{
//	/*for (int a = 0; a < Matrix.size(); a++)
//		for (int b = 0; b < Matrix[a].size(); b++)
//		{
//			bool WhitePeak = true;
//			if(Matrix[a][b]=1)
//			{
//				do
//				{
//
//				}while(WhitePeak)
//			}
//		}*/
//	bool WhitePeak = true;
//	vector<int> copy_of_ks;
//	for (auto& ks : KS_in_Graph)
//	{
//		copy_of_ks.push_back(ks);
//	}
//	//while (WhitePeak)
//	//{
//		for (int grey_ks : KS_in_Graph)
//		{
//			vector<int> GreyPeak;
//			GreyPeak.push_back(grey_ks - 1);//делаем первую вершину серой
//			int i=0;
//			bool possibility = true;
//			bool grey_peak_found = false;
//			do
//			{
//
//				if (Matrix[grey_ks - 1][i] == 1)
//				{
//					for (auto& it : GreyPeak)
//						if (i == it)
//							grey_peak_found = true;
//					grey_ks = i + 1;
//				}
//				i++;
//			} while (i < Matrix.size() && possibility ==true);
//			//for (int i = 0; i < Matrix.size(); i++)  //проходим по строке с серой вершиной
//			//{
//			//	if(Matrix[ks-1][i]!=1 &&)
//			//	Matrix[ks - 1][i]
//			//}
//		}
//	//}
//	return false;
//}
