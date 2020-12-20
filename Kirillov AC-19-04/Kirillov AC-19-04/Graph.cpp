#include "Graph.h"
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include<vector>
#include<set>
#include<queue>

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
			edge new_edge;
			p[pipe].input = a + 1;       //Храним id
			p[pipe].output = b + 1;
			Pipes_in_Graph.insert(pipe + 1); 
			if (KS_in_Graph.find(a) != KS_in_Graph.end()) //Если данная кс уже есть в сети
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  //Ищем когда добавилась эта кс
					if (ReNumbered_ks[i] = a)
						new_edge.a = i;      //находим номер нужной нам кс//индекс и есть порядковый номер
			}
			else
			{
				KS_in_Graph.insert(a + 1);           //добавляем начальную вершину к общему списку вершин
				ReNumbered_ks.push_back(a + 1);      //Индекс этого элемента в векторе будет порядковым номером
				new_edge.a = ReNumbered_ks.size() - 1;   
			}
			//Тоже самое для конечной кс
			if (KS_in_Graph.find(b) != KS_in_Graph.end()) 
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  
					if (ReNumbered_ks[i] = b)
						new_edge.b = i;     
			}
			else
			{
				KS_in_Graph.insert(b + 1);           
				ReNumbered_ks.push_back(b + 1);      
				new_edge.b = ReNumbered_ks.size() - 1;
			}
			new_edge.cost = p[pipe].length;
			All_edges.push_back(new_edge);
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
{//Переделывать
	vector<vector<int>> matrix(ks.size(), vector<int>(ks.size()));      //Создаем матрицу исходя из кол-ва кс в базе
	for (int i = 0; i < ks.size(); i++)
		for (int j = 0; j < ks.size(); j++)
			matrix[i][j] = 0;                         //Зануляем все элементы
	for (auto &pipe_id : Pipes_in_Graph)         //Проходимся по трубам, задействованным в графе
	{
		matrix[p[pipe_id-1].input - 1][p[pipe_id-1].output - 1] = 1;      //Добавляем связь
	}
	if (Pipes_in_Graph.size() == 0)
		EmptyGraph = true;            //Информация, что граф пустой
	Matrix = matrix;         //Присваиваем готовую матрицу полю класса
	WeightMatrix = Matrix;
	for (int pipe : Pipes_in_Graph)    //заполняем матрицу весов
	{
		WeightMatrix[p[pipe - 1].input][p[pipe - 1].output] = p[pipe - 1].length; //В качестве веса длина трубы
	}
}

bool Graph::CheckLine(int index, string parametr)//Вспомогательная функция проверки строки/столбца на нули 
{
	if (parametr == "line")//Чекаем строку
	{
		for (int j = 0; j < Matrix.size(); j++)
			if (Matrix[index][j] > 0) //если есть элемент отличный от нуля возвращаем true
				return true;
	}else
	if (parametr == "column")//Чекаем столбец
	{
		for (int i = 0; i < Matrix.size(); i++)
			if (Matrix[i][index] > 0)
				return true;
	}
	return false;//Если проверка ничего не выявила
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
	unordered_set<int> CopyKS = KS_in_Graph;               //Копия вершин графа, чтобы удалять их
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

void Graph::MaxFlow(const vector<Pipe>& p, const vector<KS>& ks)
{
	CreateGraph(p, ks);
	if (EmptyGraph)
		cout << "Невозможно расчитать максимальный поток, потому что в сети нет объектов!" << endl;
	else
	{
		vector<vector<int>> WeightMatrix = Matrix;//Матрица весов
		for (int pipe : Pipes_in_Graph)    //заполняем матрицу весов
		{
			WeightMatrix[p[pipe - 1].input][p[pipe - 1].output] = p[pipe - 1].length; //В качестве веса длина трубы
		}
		set<int> KS_lines;         //Здесь кс, которые могут быть началом
		set<int> KS_columns;       //концом
		for (int beginning : KS_in_Graph)
			if (CheckLine(beginning - 1, "line"))
				KS_lines.insert(beginning);        //Добавляем кс, которые могут быть началом
		for (int end : KS_in_Graph)
			if (CheckLine(end - 1, "column"))
				KS_lines.insert(end);              //Добавляем кс, которые могут быть концом
		////////Взаимодействие с пользователем
		PrintGraph();             //Показываем пользователю сеть
		cout << "Выберите начальную кс, доступны: ";
		for (int beginning : KS_lines)
			cout << beginning << " ";       //Показываем возможные начальные вершины
		int istok;      //Исток потока сети
		while ((cin >> istok).fail() || KS_lines.find(istok) == KS_lines.end()) //Проверяем ввод на допустимость
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Введите корректное число!" << endl;
		}
		cout << "Выберите конечную кс, доступны: ";
		for (int end : KS_columns)             //Показываем возможные конечные вершины
			cout << end << " ";
		int stok;     //Сток потока сети
		while ((cin >> stok).fail() || KS_columns.find(stok) == KS_columns.end()) //Проверяем ввод на допустимость
		{
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Введите корректное число!" << endl;
		}
		/////////////Закончили операции с пользователем

	}
}

int Graph::ShortestWay(int v, int end)//v - индекс начальной вершины
{
	//CreateGraph(p, ks);
	//int C[MAX_N][MAX_N];    // Матрица "пропускных способностей"
	//int F[MAX_N][MAX_N];    // Матрица "текущего потока в графе"
	//int P[MAX_N][MAX_N];    // Матрица "стоимости (расстояний)"
	//int push[MAX_N];        // Поток в вершину [v] из начальной точки
	//int mark[MAX_N];        // Отметки на вершинах, в которых побывали
	//int pred[MAX_N];        // Откуда пришли в вершину [v] (предок)
	//int dist[MAX_N];        // Расстояние до вершины [v] из начальной точки
	//int N, M, s, t;         // Кол-во вершин, ребер, начальная и конечные точки
	//int max_flow;
	const int inf = 100000000;   //Бесконечность
	int NumberOfKS = KS_in_Graph.size();
	int NumberOfPipes = Pipes_in_Graph.size();
	vector<int> Distance(NumberOfKS, inf);      //храним расстояния до вершин
	/////
	if (v < NumberOfKS && v != end)
	{
		Distance[v] = 0;
		for (int i = 0; i < NumberOfKS - 1; ++i)
			//for (int j = 0; j < NumberOfPipes; ++j)
			for (int j = 0; j < NumberOfPipes; ++j)
				if (Distance[All_edges[j].a] < inf)
					Distance[All_edges[j].b] = min(Distance[All_edges[j].b], Distance[All_edges[j].a] + All_edges[j].cost);
				//if (Distance[p[pipe - 1].input] < inf)
					//Distance[p[pipe - 1].output] = min(Distance[p[pipe - 1].output], Distance[p[pipe - 1].input] + p[pipe - 1].length);
		return Distance[end];
	}
	/*for (int i = 0; i < KS_in_Graph.size(); i++)
	{
		mark[i] = 0;
		push[i] = 0;
		pred[i] = 0;
		dist[i] = MAX_VAL;
	}
	queue<int> Q;
	mark[s] = 1;
	pred[s] = s;
	push[s] = MAX_VAL;

	Q.push(s);
	while (!mark[t] && !Q.empty())
	{
		int u = Q.front(); Q.pop();
		for (int v = 1; v < N; v++)
			if (!mark[v] && (C[u][v] - F[u][v] > 0))
			{
				push[v] = min(push[u], C[u][v] - F[u][v]);
				mark[v] = 1;
				pred[v] = u;
				Q.push(v);
			}
	}

	return mark[t];*/
}

bool Graph::CheckCycle()
{
	//bool WhitePeak = true;
	//vector<int> copy_of_ks;
	//for (auto& ks : KS_in_Graph)
	//{
	//	copy_of_ks.push_back(ks);
	//}
	////while (WhitePeak)
	////{
	//	for (int grey_ks : KS_in_Graph)
	//	{
	//		vector<int> GreyPeak;
	//		GreyPeak.push_back(grey_ks - 1);//делаем первую вершину серой
	//		int i=0;
	//		bool possibility = true;
	//		bool grey_peak_found = false;
	//		do
	//		{

	//			if (Matrix[grey_ks - 1][i] == 1)
	//			{
	//				for (auto& it : GreyPeak)
	//					if (i == it)
	//						grey_peak_found = true;
	//				grey_ks = i + 1;
	//			}
	//			i++;
	//		} while (i < Matrix.size() && possibility ==true);
	//		//for (int i = 0; i < Matrix.size(); i++)  //проходим по строке с серой вершиной
	//		//{
	//		//	if(Matrix[ks-1][i]!=1 &&)
	//		//	Matrix[ks - 1][i]
	//		//}
	//	}
	////}
	
	int NumberOfKS = KS_in_Graph.size();           //Неиспользованные вершины
	vector<vector<int>> Matrix_Copy = Matrix;      //Копия матрицы смежности, чтобы занулять строки
	unordered_set<int> CopyKS = KS_in_Graph;               //Копия вершин графа, чтобы удалять их
	set<int> GreyKS;
	int index_i, index_j;
	do//Пока есть неиспользованные вершины
	{
	skip:                     //Лейбл для goto
		for (int ks : CopyKS)      //Перебираем неиспользованные вершины
		{
			GreyKS = { -1 };
			GreyKS.insert(ks - 1);//Помечаем начальную вершину
			bool VoidLine = true;         //Если строка только с 0
			bool DeletedElement = false;  //Если удалили вершину
			for (int j = 0; j < Matrix_Copy[ks - 1].size(); j++)   //Проверяем строку на занулённость
			{
				if (Matrix_Copy[ks - 1][j] == 1)
					VoidLine = false;
			}
			if (VoidLine == true)    //Если строка из нулей
			{
				//SortedKS.emplace(NumberOfKS, ks); //Добавляем вершину в список отсортированных
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
	
	return false;
}
