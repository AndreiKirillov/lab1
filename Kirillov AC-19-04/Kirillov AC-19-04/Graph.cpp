#include "Graph.h"
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include <vector>
#include<set>

void Graph::ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks)
{
	if (p.size() == 0 || ks.size() < 2 || (p.size() == 0 && ks.size() < 2))    //Проверяем достаточно ли объектов
	{
		cout << "Невозможно соединить КС, так как недостаточно объектов" << endl;
	}
	else
	{
		cout << "Выберите начальную компрессорную станцию:" << endl;            // Пользователь выбирает нужные объекты
		vector<int> begin = UserChooseKS(ks, 1);
		int a = begin[0];
		cout << "Выберите конечную компрессорную станцию:" << endl;            //////Сделать потом чтоб не заставлять выбирать если ошибка
		vector<int> end = UserChooseKS(ks, 1);
		int b = end[0];                                                             // а, b, pipe - индекс
		cout << "Выберите трубу для соединения компрессорных станций:" << endl;
		vector<int> v = FindPipe(p, 1);
		int pipe = v[0];   //////Труба должна быть не в ремонте
		if (a >= 0 && b >= 0 && a != b && pipe >= 0)       //Если всё нормально
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
		}
	}
}

vector<vector<int>> Graph::CreateGraph(const vector<Pipe>& p, const vector<KS>& ks)
{
	vector<vector<int>> matrix(ks.size(), vector<int>(ks.size()));
	/*for(int pipe_index = 0; pipe_index < p.size(); pipe_index++)                      
		for (int ks_index = 0; ks_index < ks.size(); ks_index++)             
		{
			if (p[pipe_index].input == ks[ks_index].id)
				matrix[pipe_index][ks_index] = 1;
			else
				if (p[pipe_index].output == ks[ks_index].id)
					matrix[pipe_index][ks_index] = -1;
				else
					matrix[pipe_index][ks_index] = 0;
		}*/
	for (int i = 0; i < ks.size(); i++)
		for (int j = 0; j < ks.size(); j++)
			matrix[i][j] = 0;
	for (auto &pipe_id : Pipes_in_Graph)
	{
		matrix[p[pipe_id].input - 1][p[pipe_id].output - 1] = 1;
	}
	return matrix;
}

void Graph::PrintGraph(const vector<vector<int>>& matrix)
{
	//Список смежности
	cout << "Компрессорная станция - смежные с ней станции" << endl;
	for (int i = 0; i < matrix.size(); i++)
	{
		bool endline = false;
		for (int j = 0; j < matrix[i].size(); j++)
			if (matrix[i][j] == 1)
			{
				if (endline == false)
				{
					cout << i << "/t-/t" << j;
					endline = true;
				}
				else
					cout << ", " << j;
			}
		if (endline == true)
			cout << endl;
	}
	cout << endl;
}
