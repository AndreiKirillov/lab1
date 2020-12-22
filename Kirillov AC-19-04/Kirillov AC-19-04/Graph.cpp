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
		cout << "Выберите конечную компрессорную станцию:" << endl;            
		vector<int> end = UserChooseKS(ks, 1);
		int b = end[0];                                                             // а, b, pipe - индекс
		cout << "Выберите трубу для соединения компрессорных станций:" << endl;
		vector<int> v = FindPipe(p, 1);
		int pipe = v[0];   
		if (p[pipe].remont == true || Pipes_in_Graph.find(p[pipe].id) != Pipes_in_Graph.end())
		{
			PotentialError = true;            //Труба не должна быть в ремонте или уже быть использованной в сети
			cout << "Нельзя использовать данную трубу!" << endl;
		}
		if (a >= 0 && b >= 0 && a != b && pipe >= 0 && !PotentialError)       //Если всё нормально
		{
			edge new_edge;
			p[pipe].input = ks[a].id;       //Храним id
			p[pipe].output = ks[b].id;
			Pipes_in_Graph.insert(p[pipe].id); 
			if (KS_in_Graph.find(ks[a].id) != KS_in_Graph.end()) //Если данная кс уже есть в сети
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  //Ищем когда добавилась эта кс
					if (ReNumbered_ks[i] == ks[a].id)
						new_edge.a = i;      //находим номер нужной нам кс//индекс и есть порядковый номер
			}
			else
			{
				KS_in_Graph.insert(ks[a].id);           //добавляем начальную вершину к общему списку вершин
				ReNumbered_ks.push_back(ks[a].id);      //Индекс этого элемента в векторе будет порядковым номером
				new_edge.a = ReNumbered_ks.size() - 1;   
			}
			//Тоже самое для конечной кс
			if (KS_in_Graph.find(ks[b].id) != KS_in_Graph.end()) 
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  
					if (ReNumbered_ks[i] == ks[b].id)
						new_edge.b = i;  
			}
			else
			{
				KS_in_Graph.insert(ks[b].id);           
				ReNumbered_ks.push_back(ks[b].id);
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

void Graph::CreateGraph()   //Функция создания матрицы смежности
{//Переделывать
	if (Pipes_in_Graph.size() == 0)
		EmptyGraph = true;//Информация, что граф пустой
	else
	{
		vector<vector<int>> matrix(KS_in_Graph.size(), vector<int>(KS_in_Graph.size()));      //
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[i].size(); j++)
				matrix[i][j] = 0;                //
		for (auto ed : All_edges)
			matrix[ed.a][ed.b] = 1;
		Matrix = matrix;
		
		//WeightMatrix = Matrix;
		//for (int pipe : Pipes_in_Graph)    //заполняем матрицу весов
		//{
		//	WeightMatrix[p[pipe - 1].input][p[pipe - 1].output] = p[pipe - 1].length; //В качестве веса длина трубы
		//}
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
	CreateGraph();
	//Выводим список смежности
	if (!EmptyGraph)        //Выводим граф только, если матрица не пустая
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
						cout << ReNumbered_ks[i] << "\t-\t" << ReNumbered_ks[j];       //Выводим id
						endline = true;
					}
					else
						cout << ", " << ReNumbered_ks[j];
				}
			if (endline)
				cout << endl;
		}
		cout << endl;
	}
	else
		cout << "Газотранспортной сети не существует, так как нет связей между компрессорными станциями" << endl;
}

bool Graph::CheckCycle(vector<int>& visited_ks, int beginning)
{
	visited_ks[beginning] = 1;
	for (int j = 0; j < Matrix[beginning].size(); j++)
		if (Matrix[beginning][j] != 0) {
			if (visited_ks[j] == 0) {
				if (CheckCycle(visited_ks, j)) return true;
			}
			else if (visited_ks[j] == 1)
				return true;
		}
	return false;
}

void Graph::TopologicalSort()       //Функция топологической сортировки
{
	CreateGraph();
	bool cycle = false;
	for (int i = 0; i < Matrix.size(); i++)
	{
		vector<int> visited_ks(Matrix.size(), 0);
		if (CheckCycle(visited_ks,0))
		{
			cout << "Топологическая сортировка невозможна, в сети обнаружены циклы!" << endl;
			cycle = true;
			break;
		}
	}
	if (!cycle)
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
				ks = ConvertKS(ks);
				bool VoidLine = true;         //Если строка только с 0
				bool DeletedElement = false;  //Если удалили вершину
				for (int j = 0; j < Matrix_Copy[ks].size(); j++)   //Проверяем строку на занулённость
				{
					if (Matrix_Copy[ks][j] == 1)
						VoidLine = false;
				}
				if (VoidLine == true)    //Если строка из нулей
				{
					SortedKS.emplace(NumberOfKS, ReNumbered_ks[ks]); //Добавляем вершину в список отсортированных
					NumberOfKS--;                     //Уменьшаем
					for (int i = 0; i < Matrix_Copy.size(); i++)
						Matrix_Copy[i][ks] = 0;               //Зануляем элементы использованной вершины
					CopyKS.erase(ReNumbered_ks[ks]);                 //Помечаем вершину как использованную
					DeletedElement = true;
				}
				if (DeletedElement)       //Если удалили вершину, начинаем цикл заново
					goto skip;
			}
		} while (NumberOfKS > 0);
		////Выводим результат
		cout << "\tТопографическая сортировка\t\n\n";
		cout << "№ КС - id КС" << endl << endl;
		for (auto& n : SortedKS)
		{
			cout << n.first << "\t" << n.second << endl;
		}
	}
}

void Graph::MaxFlow(int u, int v)
{
	if (EmptyGraph)
		cout << "Невозможно расчитать максимальный поток, потому что в сети нет объектов!" << endl;
	else
	{
		vector<vector<int>> matrix(KS_in_Graph.size(), vector<int>(KS_in_Graph.size()));      //Создаем матрицу исходя из кол-ва кс в базе
		vector<vector<int>> WeightMatrix = matrix;//Матрица весов
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[i].size(); j++)
			{
				matrix[i][j] = 0;                //Зануляем все элементы
				WeightMatrix[i][j] = 0;
			}
		for (auto ed : All_edges)
		{
			matrix[ConvertKS(ed.a)][ConvertKS(ed.b)] = 1;               //Создали матрицу из порядковых номеров от 0 до n
			WeightMatrix[ConvertKS(ed.a)][ConvertKS(ed.b)] = ed.cost;   //Заполняем матрицу весов
		}
		//Matrix = matrix;
		bool new_way = true; 
		int Flow;
		vector<edge> Copy_edges = All_edges;
		do
		{

		} while (new_way);
	}
}

int Graph::ShortestWay(int v, int end)//v и end - порядковые номера начальной вершины и конечной
{
	const int inf = 100000000;   //Бесконечность
	int NumberOfKS = KS_in_Graph.size();
	int NumberOfPipes = Pipes_in_Graph.size();
	vector<int> Distance(NumberOfKS, inf);      //храним расстояния до вершин
		Distance[v] = 0;
		for (int i = 0; i < NumberOfKS - 1; ++i)
			for (int j = 0; j < NumberOfPipes; ++j)
				if (Distance[All_edges[j].a] < inf)
					Distance[All_edges[j].b] = min(Distance[All_edges[j].b], Distance[All_edges[j].a] + All_edges[j].cost);
		return Distance[end];
}

int Graph::ConvertKS(int ks_id)    //Принимаем id кс
{
	for (int i = 0; i < ReNumbered_ks.size(); i++)  
		if (ReNumbered_ks[i] == ks_id)  
			return i;                 //Возвращаем порядковый номер кс
}

//int Graph::UserChooseKS_inGraph(set<int>& set_ks)
//{
//	for (int i : set_ks)
//		cout << i << " ";       //Показываем возможные вершины
//	int choosen_ks;      
	//while ((cin >> choosen_ks).fail() || set_ks.find(choosen_ks) == set_ks.end()) //Проверяем ввод на допустимость
	//{
	//	cin.clear();
	//	cin.ignore(32767, '\n');
	//	cout << "Введите корректное число!" << endl;
	//}
//	return ConvertKS(choosen_ks);  //Возвращаем порядковый номер
//}

ofstream& operator<<(ofstream& outf, const Graph& g)
{
	for (int i : g.Pipes_in_Graph)
		outf << i << endl;
	for (int i : g.KS_in_Graph)
		outf << i << endl;
	for (int i = 0; i < g.ReNumbered_ks.size(); i++)
		outf << g.ReNumbered_ks[i] << endl;
	/*for (int i : g.KS_lines)
		outf << i << endl;
	for (int i : g.KS_columns)
		outf << i << endl;*/
	for (int i = 0; i < g.All_edges.size(); i++)
	{
		outf << g.All_edges[i].a << endl;
		outf << g.All_edges[i].b << endl;
		outf << g.All_edges[i].cost << endl;
	}
	return outf;
}
