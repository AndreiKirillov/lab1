#include "Graph.h"
#include"Source.h"
#include"Pipe.h"
#include"KS.h"
#include<vector>
#include<set>
#include<queue>

void Graph::ConnectKSbyPipe(vector<Pipe>& p, const vector<KS>& ks)             //Ôóíêöèÿ äîáàâëåíèÿ ñâÿçè ìåæäó êñ
{
	if (p.size() == 0 || ks.size() < 2 || (p.size() == 0 && ks.size() < 2))    //Ïðîâåðÿåì äîñòàòî÷íî ëè îáúåêòîâ
	{
		cout << "Íåâîçìîæíî ñîåäèíèòü ÊÑ, òàê êàê íåäîñòàòî÷íî îáúåêòîâ" << endl;
	}
	else
	{
		bool PotentialError = false;
		cout << "Âûáåðèòå íà÷àëüíóþ êîìïðåññîðíóþ ñòàíöèþ:" << endl;            // Ïîëüçîâàòåëü âûáèðàåò íóæíûå îáúåêòû
		vector<int> begin = UserChooseKS(ks, 1);
		int a = begin[0];
		cout << "Âûáåðèòå êîíå÷íóþ êîìïðåññîðíóþ ñòàíöèþ:" << endl;            //////Ñäåëàòü ïîòîì ÷òîá íå çàñòàâëÿòü âûáèðàòü åñëè îøèáêà
		vector<int> end = UserChooseKS(ks, 1);
		int b = end[0];                                                             // à, b, pipe - èíäåêñ
		cout << "Âûáåðèòå òðóáó äëÿ ñîåäèíåíèÿ êîìïðåññîðíûõ ñòàíöèé:" << endl;
		vector<int> v = FindPipe(p, 1);
		int pipe = v[0];   
		if (p[pipe].remont == true || Pipes_in_Graph.find(pipe + 1) != Pipes_in_Graph.end())
		{
			PotentialError = true;            //Òðóáà íå äîëæíà áûòü â ðåìîíòå èëè óæå áûòü èñïîëüçîâàííîé â ñåòè
			cout << "Íåëüçÿ èñïîëüçîâàòü äàííóþ òðóáó!" << endl;
		}
		if (a >= 0 && b >= 0 && a != b && pipe >= 0 && !PotentialError)       //Åñëè âñ¸ íîðìàëüíî
		{
			edge new_edge;
			p[pipe].input = a + 1;       //Õðàíèì id
			p[pipe].output = b + 1;
			Pipes_in_Graph.insert(pipe + 1); 
			if (KS_in_Graph.find(a+1) != KS_in_Graph.end()) //Åñëè äàííàÿ êñ óæå åñòü â ñåòè
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  //Èùåì êîãäà äîáàâèëàñü ýòà êñ
					if (ReNumbered_ks[i] == a+1)
						new_edge.a = i;      //íàõîäèì íîìåð íóæíîé íàì êñ//èíäåêñ è åñòü ïîðÿäêîâûé íîìåð
				KS_lines.insert(a + 1);
			}
			else
			{
				KS_in_Graph.insert(a + 1);           //äîáàâëÿåì íà÷àëüíóþ âåðøèíó ê îáùåìó ñïèñêó âåðøèí
				ReNumbered_ks.push_back(a + 1);      //Èíäåêñ ýòîãî ýëåìåíòà â âåêòîðå áóäåò ïîðÿäêîâûì íîìåðîì
				new_edge.a = ReNumbered_ks.size() - 1;   
				KS_lines.insert(a + 1);
			}
			//Òîæå ñàìîå äëÿ êîíå÷íîé êñ
			if (KS_in_Graph.find(b+1) != KS_in_Graph.end()) 
			{
				for (int i = 0; i < ReNumbered_ks.size(); i++)  
					if (ReNumbered_ks[i] == b+1)
						new_edge.b = i;  
				KS_columns.insert(b + 1);
			}
			else
			{
				KS_in_Graph.insert(b + 1);           
				ReNumbered_ks.push_back(b + 1);      
				new_edge.b = ReNumbered_ks.size() - 1;
				KS_columns.insert(b + 1);
			}
			new_edge.cost = p[pipe].length;
			All_edges.push_back(new_edge);
		}
		else
		{
			cout << "Îøèáêà! Ïîïðîáóéòå çàíîâî!" << endl;
			if (a == b)
				cout << "Íåîáõîäèìî óêàçûâàòü ðàçíûå êîìïðåññîðíûå ñòàíöèè!" << endl;
		}
	}
}

void Graph::CreateGraph()   //Ôóíêöèÿ ñîçäàíèÿ ìàòðèöû ñìåæíîñòè
{//Ïåðåäåëûâàòü
	if (Pipes_in_Graph.size() == 0)
		EmptyGraph = true;//Èíôîðìàöèÿ, ÷òî ãðàô ïóñòîé
	else
	{
		vector<vector<int>> matrix(KS_in_Graph.size(), vector<int>(KS_in_Graph.size()));      //Ñîçäàåì ìàòðèöó èñõîäÿ èç êîë-âà êñ â áàçå
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[i].size(); j++)
				matrix[i][j] = 0;                //Çàíóëÿåì âñå ýëåìåíòû
		for (auto ed : All_edges)
			matrix[ed.a][ed.b] = 1;
		Matrix = matrix;
		//vector<vector<int>> matrix(ks.size(), vector<int>(ks.size()));      //Ñîçäàåì ìàòðèöó èñõîäÿ èç êîë-âà êñ â áàçå

		//for (int i = 0; i < ks.size(); i++)
		//	for (int j = 0; j < ks.size(); j++)
		//		matrix[i][j] = 0;                         //Çàíóëÿåì âñå ýëåìåíòû
		//for (auto& pipe_id : Pipes_in_Graph)         //Ïðîõîäèìñÿ ïî òðóáàì, çàäåéñòâîâàííûì â ãðàôå
		//{
		//	matrix[p[pipe_id - 1].input - 1][p[pipe_id - 1].output - 1] = 1;      //Äîáàâëÿåì ñâÿçü
		//}
		//Matrix = matrix;         //Ïðèñâàèâàåì ãîòîâóþ ìàòðèöó ïîëþ êëàññà
		//WeightMatrix = Matrix;
		//for (int pipe : Pipes_in_Graph)    //çàïîëíÿåì ìàòðèöó âåñîâ
		//{
		//	WeightMatrix[p[pipe - 1].input][p[pipe - 1].output] = p[pipe - 1].length; //Â êà÷åñòâå âåñà äëèíà òðóáû
		//}
	}
}

//bool Graph::CheckLine(int index, string parametr)//Âñïîìîãàòåëüíàÿ ôóíêöèÿ ïðîâåðêè ñòðîêè/ñòîëáöà íà íóëè 
//{
//	if (parametr == "line")//×åêàåì ñòðîêó
//	{
//		for (int j = 0; j < Matrix.size(); j++)
//			if (Matrix[index][j] > 0) //åñëè åñòü ýëåìåíò îòëè÷íûé îò íóëÿ âîçâðàùàåì true
//				return true;
//	}else
//	if (parametr == "column")//×åêàåì ñòîëáåö
//	{
//		for (int i = 0; i < Matrix.size(); i++)
//			if (Matrix[i][index] > 0)
//				return true;
//	}
//	return false;//Åñëè ïðîâåðêà íè÷åãî íå âûÿâèëà
//}

void Graph::PrintGraph()        //Ôóíêöèÿ âûâîäà ãðàôà â êîíñîëü
{
	CreateGraph();
	//Âûâîäèì ñïèñîê ñìåæíîñòè
	if (!EmptyGraph)        //Âûâîäèì ãðàô òîëüêî, åñëè ìàòðèöà íå ïóñòàÿ
	{
		cout << "\tÃàçîòðàíñïîðòíàÿ ñåòü\t\n\n" <<
			"Êîìïðåññîðíàÿ ñòàíöèÿ <---> ñìåæíûå ñ íåé ñòàíöèè" << endl << endl;
		for (int i = 0; i < Matrix.size(); i++)
		{
			bool endline = false;                      //Ïåðåìåííàÿ ÷òîáû çíàòü, íóæíî ëè ïåðåâîäèòü ñòðîêó
			for (int j = 0; j < Matrix[i].size(); j++)
				if (Matrix[i][j] == 1)
				{
					if (endline == false)
					{
						cout << ReNumbered_ks[i] << "\t-\t" << ReNumbered_ks[j];       //Âûâîäèì id
						endline = true;
					}
					else
						cout << ", " << j+1;
				}
			if (endline)
				cout << endl;
		}
		cout << endl;
	}
	else
		cout << "Ãàçîòðàíñïîðòíîé ñåòè íå ñóùåñòâóåò, òàê êàê íåò ñâÿçåé ìåæäó êîìïðåññîðíûìè ñòàíöèÿìè" << endl;
}

void Graph::TopologicalSort()       //Ôóíêöèÿ òîïîëîãè÷åñêîé ñîðòèðîâêè
{
	CreateGraph();
	map<int, int> SortedKS;     //êëþ÷ - íîìåð âåðøèíû, çíà÷åíèå - id ÊÑ
	int NumberOfKS = KS_in_Graph.size();           //Íåèñïîëüçîâàííûå âåðøèíû
	vector<vector<int>> Matrix_Copy = Matrix;      //Êîïèÿ ìàòðèöû ñìåæíîñòè, ÷òîáû çàíóëÿòü ñòðîêè
	unordered_set<int> CopyKS = KS_in_Graph;               //Êîïèÿ âåðøèí ãðàôà, ÷òîáû óäàëÿòü èõ
	do//Ïîêà åñòü íåèñïîëüçîâàííûå âåðøèíû
	{
	skip:                     //Ëåéáë äëÿ goto
		for (int ks : CopyKS)      //Ïåðåáèðàåì íåèñïîëüçîâàííûå âåðøèíû
		{
			ks = ConvertKS(ks);
			bool VoidLine = true;         //Åñëè ñòðîêà òîëüêî ñ 0
			bool DeletedElement = false;  //Åñëè óäàëèëè âåðøèíó
			for (int j = 0; j < Matrix_Copy[ks].size(); j++)   //Ïðîâåðÿåì ñòðîêó íà çàíóë¸ííîñòü
			{
				if (Matrix_Copy[ks][j] == 1)
					VoidLine = false;
			}
			if (VoidLine == true)    //Åñëè ñòðîêà èç íóëåé
			{
				SortedKS.emplace(NumberOfKS, ReNumbered_ks[ks]); //Äîáàâëÿåì âåðøèíó â ñïèñîê îòñîðòèðîâàííûõ
				NumberOfKS--;                     //Óìåíüøàåì
				for (int i = 0; i < Matrix_Copy.size(); i++)
					Matrix_Copy[i][ks] = 0;               //Çàíóëÿåì ýëåìåíòû èñïîëüçîâàííîé âåðøèíû
				CopyKS.erase(ReNumbered_ks[ks]);                 //Ïîìå÷àåì âåðøèíó êàê èñïîëüçîâàííóþ
				DeletedElement = true;
			}
			if (DeletedElement)       //Åñëè óäàëèëè âåðøèíó, íà÷èíàåì öèêë çàíîâî
				goto skip;
		}
	} while (NumberOfKS > 0);
	////Âûâîäèì ðåçóëüòàò
	cout << "\tÒîïîãðàôè÷åñêàÿ ñîðòèðîâêà\t\n\n";
	cout << "¹ ÊÑ - id ÊÑ" << endl << endl;
	for(auto& n :SortedKS)
	{
		cout << n.first << "\t" << n.second << endl;
	}
}


void Graph::MaxFlow()
{
	CreateGraph();

	if (EmptyGraph)
		cout << "Íåâîçìîæíî ðàñ÷èòàòü ìàêñèìàëüíûé ïîòîê, ïîòîìó ÷òî â ñåòè íåò îáúåêòîâ!" << endl;
	else
	{
		vector<vector<int>> matrix(KS_in_Graph.size(), vector<int>(KS_in_Graph.size()));      //Ñîçäàåì ìàòðèöó èñõîäÿ èç êîë-âà êñ â áàçå
		vector<vector<int>> WeightMatrix = matrix;//Ìàòðèöà âåñîâ
		for (int i = 0; i < matrix.size(); i++)
			for (int j = 0; j < matrix[i].size(); j++)
			{
				matrix[i][j] = 0;                //Çàíóëÿåì âñå ýëåìåíòû
				WeightMatrix[i][j] = 0;
			}
		for (auto ed : All_edges)
		{

			//WeightMatrix[p[pipe - 1].input][p[pipe - 1].output] = p[pipe - 1].length; //Â êà÷åñòâå âåñà äëèíà òðóáû
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

int Graph::ShortestWay(int v, int end)//v è end - ïîðÿäêîâûå íîìåðà íà÷àëüíîé âåðøèíû è êîíå÷íîé
{
	const int inf = 100000000;   //Áåñêîíå÷íîñòü
	int NumberOfKS = KS_in_Graph.size();
	int NumberOfPipes = Pipes_in_Graph.size();
	vector<int> Distance(NumberOfKS, inf);      //õðàíèì ðàññòîÿíèÿ äî âåðøèí
		Distance[v] = 0;
		for (int i = 0; i < NumberOfKS - 1; ++i)
			for (int j = 0; j < NumberOfPipes; ++j)
				if (Distance[All_edges[j].a] < inf)
					Distance[All_edges[j].b] = min(Distance[All_edges[j].b], Distance[All_edges[j].a] + All_edges[j].cost);
		return Distance[end];
}

int Graph::ConvertKS(int ks_id)    //Ïðèíèìàåì id êñ
{
	for (int i = 0; i < ReNumbered_ks.size(); i++)  
		if (ReNumbered_ks[i] == ks_id)  
			return i;                 //Âîçâðàùàåì ïîðÿäêîâûé íîìåð êñ
}

int Graph::UserChooseKS_inGraph(set<int>& set_ks)
{
	for (int i : set_ks)
		cout << i << " ";       //Ïîêàçûâàåì âîçìîæíûå âåðøèíû
	int choosen_ks;      
	while ((cin >> choosen_ks).fail() || set_ks.find(choosen_ks) == set_ks.end()) //Ïðîâåðÿåì ââîä íà äîïóñòèìîñòü
	{
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Ââåäèòå êîððåêòíîå ÷èñëî!" << endl;
	}
	return ConvertKS(choosen_ks);  //Âîçâðàùàåì ïîðÿäêîâûé íîìåð
}

bool Graph::CheckCycle()
{
	for (int beginning = 0; beginning < Matrix.size(); beginning++)
	{
		bool no_way = false;
		vector<int> visited_ks(Matrix.size(), 0);
		visited_ks[beginning] = 1; 
		for (int j = 0; j < Matrix[beginning].size(); j++)
			if (Matrix[beginning][j] != 0) {
				if (visited_ks[j] == 0) {
					//if (cycle_exists(j, g, visit)) return true;
				}
				else if (visited_ks[j] == 1)
					return true;
			}
	}
	return false;
	
	int NumberOfKS = KS_in_Graph.size();           //Íåèñïîëüçîâàííûå âåðøèíû
	vector<vector<int>> Matrix_Copy = Matrix;      //Êîïèÿ ìàòðèöû ñìåæíîñòè, ÷òîáû çàíóëÿòü ñòðîêè
	unordered_set<int> CopyKS = KS_in_Graph;               //Êîïèÿ âåðøèí ãðàôà, ÷òîáû óäàëÿòü èõ
	set<int> GreyKS;
	int index_i, index_j;
	do//Ïîêà åñòü íåèñïîëüçîâàííûå âåðøèíû
	{
		for (int ks : CopyKS)      //Ïåðåáèðàåì íåèñïîëüçîâàííûå âåðøèíû
		{
			vector<int> visited_ks(Matrix.size(), 0);
			ks = ConvertKS(ks);
			visited_ks[ks] = 1;
			bool VoidLine = true;         //Åñëè ñòðîêà òîëüêî ñ 0
			bool DeletedElement = false;  //Åñëè óäàëèëè âåðøèíó
			//do
			//{
			    skip:
				for (int j = 0; j < Matrix_Copy[ks].size(); j++)   
				{
					if (Matrix_Copy[ks][j] == 1 && visited_ks[j] == 0)
					{
						Matrix_Copy[ks][j] = 0;
						ks = j;
						visited_ks[j] = 1;
						goto skip;
					}
					else if (Matrix_Copy[ks][j] == 1 && visited_ks[j] == 1)
						return true;
				}
			//}
			if (VoidLine == true)    //Åñëè ñòðîêà èç íóëåé
			{
				//SortedKS.emplace(NumberOfKS, ReNumbered_ks[ks]); //Äîáàâëÿåì âåðøèíó â ñïèñîê îòñîðòèðîâàííûõ
				NumberOfKS--;                     //Óìåíüøàåì
				for (int i = 0; i < Matrix_Copy.size(); i++)
					Matrix_Copy[i][ks] = 0;               //Çàíóëÿåì ýëåìåíòû èñïîëüçîâàííîé âåðøèíû
				CopyKS.erase(ReNumbered_ks[ks]);                 //Ïîìå÷àåì âåðøèíó êàê èñïîëüçîâàííóþ
				DeletedElement = true;
			}
			if (DeletedElement)       //Åñëè óäàëèëè âåðøèíó, íà÷èíàåì öèêë çàíîâî
				goto skip;
			
		}
	} while (NumberOfKS > 0);
	
	return false;
}

ofstream& operator<<(ofstream& outf, const Graph& g)
{
	for (int i : g.Pipes_in_Graph)
		outf << i << endl;
	for (int i : g.KS_in_Graph)
		outf << i << endl;
	for (int i = 0; i < g.ReNumbered_ks.size(); i++)
		outf << g.ReNumbered_ks[i] << endl;
	for (int i : g.KS_lines)
		outf << i << endl;
	for (int i : g.KS_columns)
		outf << i << endl;
	for (int i = 0; i < g.All_edges.size(); i++)
	{
		outf << g.All_edges[i].a << endl;
		outf << g.All_edges[i].b << endl;
		outf << g.All_edges[i].cost << endl;
	}
	return outf;
}
