#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
#include "Graph.h"
#include "Vertex.h"


// deklaracje metod z klasy Graph

void Graph::generateGraph()
{
	srand(time(NULL));

	n = 3; //minimalna ilosc wierzcholkow maybe
	n += rand() % 10;//10000; // liczba wierzcholkow [mniejsza od 10003 dla testow na razie]
	//std::cout << n<<std::endl;
	v.resize(n);
	for (int i = 0; i < v.size(); i++)//generacja wszystkich wierzcholkow
	{
		float x = (rand() % 20000 - 10000) / 100.0; //moga byc ujemne
		float y = (rand() % 20000 - 10000) / 100.0;
		v[i].setCoords(x, y);
		v[i].setid(i);
		v[i].setGroupid(0);
		v[i].setIsLeader(false);
	}

	factory = rand() % n; // generacja polozenia fabryki;

	for (int i = 0; i < v.size(); i++)//generacja krawedzi z kazdego wierzcholka po kolei
	{
		std::vector<std::tuple<int, float, float>>* e = v[i].getEdges();
		int numberOfEdges = rand() % (n - 1); //losowanie ilosci krawedzi idacych z tego wierzcholka
		e->resize(numberOfEdges);

		std::vector<int> alreadyIn;
		int id = v[i].getid();
		for (int j = 0; j < n; j++)
		{
			if (id == j)
			{
				alreadyIn.push_back(1);
			}
			else
			{
				alreadyIn.push_back(0);
			}
		}

		//std::cout << "liczba wierz wylosowana: " << numberOfEdges << std::endl; - debug

		for (int j = 0; j < numberOfEdges; j++)
		{
			int addingVertID = rand() % n;
			while (alreadyIn[addingVertID] == 1)
			{
				addingVertID = rand() % n;
			}
			alreadyIn[addingVertID] = 1;

			std::get<0>((*e)[j]) = addingVertID;
			//std::cout << (*e)[j].first << std::endl;
			std::get<1>((*e)[j]) = rand() % 10000 / 100.0; //losowanie przep³ywu
			std::get<2>((*e)[j]) = 0; // ustawienie aktualnego przeplywu na 0
			//std::cout << (*e)[j].second << std::endl;

			//alreadyIn.erase(alreadyIn.begin() + addingVertID); - niepotrzebne kompletnie
		}
	}

}

void Graph::dfsForFix(int id, int groupid)
{
	v[id].setGroupid(groupid);
	for (int i = 0; i < v[id].getEdges()->size(); i++)
	{
		if (v[std::get<0>((*v[id].getEdges())[i])].getGroupid() == 0)
		{
			dfsForFix(std::get<0>((*v[id].getEdges())[i]), groupid);
		}
	}
}

int Graph::ifConnected()
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].getGroupid() == 0)
		{
			return i;
		}
	}
	return -1;
}

void Graph::fixGeneratedGraph()
{
	int groupid = 1;
	dfsForFix(factory, groupid);
	while (ifConnected() != -1)
	{
		int newid = ifConnected();
		groupid++;
		v[newid].setIsLeader(true);
		dfsForFix(newid, groupid);
	}

	if (groupid > 1) //jesli powyzsza petla wykonala sie chociaz raz
	{
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i].getIsLeader() == true)
			{
				v[factory].getEdges()->push_back(std::make_tuple(i, rand() % 10000 / 100.0, 0)); // tworzenie nowej krawedzi od fabryki do wczesniej nieosiagalnej czesci grafu i losowanie przeplywu
			}
		}
	}
}

void Graph::inputGraph()
{
	;
	std::cout << "Podaj ilosc wierzcholkow:\n";

	while (!(std::cin >> n) || n < 0)
	{
		std::cin.clear(); //czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
		std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
	}

	v.resize(n);
	for (int i = 0; i < v.size(); i++)//wpisanie wszystkich wierzcholkow
	{
		int x, y;
		std::cout << "Podaj koordynaty wierzcholka o id: " << i << '\n';
		while (!(std::cin >> x >> y))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Niepoprawne koordynaty wierzcholkow, podaj jeszcze raz:\n";
		}
		v[i].setCoords(x, y);
		v[i].setid(i);
		v[i].setGroupid(0);
		v[i].setIsLeader(false);
	}

	for (int i = 0; i < v.size(); i++)//wpisanie krawedzi wychodzacych z wierzcholkow
	{
		int numberOfEdges;
		std::cout << "Podaj do ilu wierzcholkow mozna dojsc z wierzcholka o id: " << i << '\n';

		while (!(std::cin >> numberOfEdges) || !(numberOfEdges >= 0 && numberOfEdges < n))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
		}

		v[i].getEdges()->resize(numberOfEdges);
		if (numberOfEdges != 0)
		{
			std::cout << "Podaj te wierzcholki: \n";
		}
		std::vector <int> contains; //do sprawdzenia czy ten juz byl podany

		for (int j = 0; j < numberOfEdges; j++)
		{
			int tempID;
			float tempFlow;
			std::cout << "Podaj id wierzcholka z ktorym ten jest polaczony:\n";

			while (!(std::cin >> tempID) || tempID < 0 || tempID == i || tempID >= n)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Bledne id; podaj jeszcze raz:\n";
			}

			while (std::find(contains.begin(), contains.end(), tempID) != contains.end())
			{
				std::cout << "To id bylo juz podane; podaj jeszcze raz:\n";
			}

			contains.push_back(tempID);

			std::get<0>((*v[i].getEdges())[j]) = tempID;

			std::cout << "Podaj maksymalny przeplyw krawedzi laczacej te wierzcholki:\n";

			while (!(std::cin >> tempFlow) || tempFlow < 0)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Niepoprawna wartosc; podaj jeszcze raz:\n";
			}
			std::get<1>((*v[i].getEdges())[j]) = tempFlow;

			//std::cin >> (*v[i].getEdges())[j].first >> (*v[i].getEdges())[j].second; // ze starej wersji bez sprawdzania poprawnosci inputu
		}

	}
	std::cout << "Podaj id wierzcholka w ktorym jest fabryka: \n";

	while (!(std::cin >> factory) || factory < 0 || factory >= n)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Bledne id; podaj jeszcze raz:\n";
	}
}

void Graph::probaOutputu()
{
	std::cout << n << '\n';
}

void Graph::setn(int n)
{
	this->n = n;
}

void Graph::outputGraph() //wyswietla graf
{
	std::cout << "ilosc wierzcholkow: " << n << '\n';
	std::cout << "id wierzcholka w ktorym jest fabryka: " << factory << '\n';
	std::cout << "-----------------\n";

	for (int i = 0; i < n; i++)
	{
		std::cout << "id wierzholka: " << i << '\n';
		//std::cout << "groupid wierzholka: " << v[i].getGroupid() << '\n'; //----- do sprawdzenia dzialania fixGeneratedGraph()
		std::cout << "x: " << v[i].getx() << " y: " << v[i].gety() << '\n';
		std::cout << "mozna z niego dojsc do: |id(max przeplyw)| ";
		if (v[i].getEdges()->empty())
		{
			std::cout << "zadnego";
		}
		else
		{
			for (int j = 0; j < v[i].getEdges()->size(); j++)
			{
				std::cout << std::get<0>((*v[i].getEdges())[j]) << "(" << std::get<1>((*v[i].getEdges())[j]) << ") ";
			}
		}

		std::cout << '\n';
	}
}



std::vector<Vertex> Graph::getShortestPathBFS(int endnode)
{
	std::vector<Vertex> shortestPath;
	std::vector<int> previous(n, -1); // zbior poprzednikow
	std::vector<bool> visited(n, false);
	std::queue<int> line; //do bfsa - kolejka, do dfa - stos

	if (v.size() == 0)
	{
		return shortestPath; // pusty wektor, nwm czy nie lepiej wtedy -1, burza mozgow jest potrzebna
	}

	line.push(factory);
	visited[factory] = true; //odwiedzamy fabryke jako pierwsza

	while (!line.empty())
	{
		int current = line.front(); //bedziemy walczyc z pierwszym elementem kolejki
		line.pop();


		if (current == endnode) break; //jesli dotrzemy do ostatniego to znaczy, ze nie musimy juz dalej szukac


		for (std::pair<int, float> neighbour : (*v[current].getEdges())) // przechodzimy po kolei po wszystkich elementach wektora edges danego wierzcholka
		{
			if (!visited[neighbour.first])
			{
				visited[neighbour.first] = true;
				previous[neighbour.first] = current;
				line.push(neighbour.first);
			}
		}
	}

	for (int i = endnode; i != factory; i = previous[i])
	{
		shortestPath.push_back(v[i]);
	}

	shortestPath.push_back(v[factory]);


	return shortestPath;

}

float Graph:: maximumFlow(int endnodeId)
{
	float maxFLow = 0;
	float newFlow = FLT_MAX;
	Vertex endnode = v[endnodeId];

	std::vector<Vertex> path;

	while (true)
	{
		path = getShortestPathBFS(endnode.getid());

		if (path.size() == 0) break;

		for (int i = path.size() - 1; i > 0; i--) //szuka najmniejszej przepustowosci na sciezce
		{
			int key = path[i - 1].getid();

			std::vector<std::pair<int, float>>::iterator it = std::find_if(
				path[i].getEdges()->begin(), path[i].getEdges()->end(), 
				[&key](std::pair<int, float>& p) { return p.first == key; }); //zwraca pare, gzdie kluczem jest nastepny wierzcholek

			if (newFlow > it->second)
			{
				newFlow = it->second;
			}

		}

		maxFLow += newFlow;

		if (newFlow <= 0) break;

		for (int i = 0; i < path.size() - 1; i++)
		{
			int currentId = path[i].getid();
			int previousId = path[i + 1].getid();

			std::vector<Vertex>::iterator currentVertex = std::find_if(	//znajduje pierwszy wierzcholek, mozna pominac jesli path zawieralby reference do wierzcholkow chyba
				v.begin(), v.end(),
				[&currentId](Vertex& p) { return p.getid() == currentId; });
			std::vector<Vertex>::iterator previousVertex = std::find_if(	//znajduje poprzednik wczesniejszego wierzcholka, mozna pominac jesli path zawieralby reference do wierzcholkow chyba
				v.begin(), v.end(),
				[&previousId](Vertex& p) { return p.getid() == previousId; });
			

			std::vector<std::pair<int, float>>::iterator toPreviousPath = std::find_if( //znajduje odpowiednia droge wychodzaca z wierzcholka
				currentVertex->getEdges()->begin(), currentVertex->getEdges()->end(),
				[previousId](std::pair<int, float>& p) { return p.first == previousId; });

			if (toPreviousPath == currentVertex->getEdges()->end())
			{
				(currentVertex->getEdges())->push_back(std::make_pair(previousId, newFlow));
			}
			else
			{
				toPreviousPath->second += newFlow;
			}


			std::vector<std::pair<int, float>>::iterator toCurrentPath = std::find_if( //znajduje odpowiednia droge wchodzaca do wierzcholka
				previousVertex->getEdges()->begin(), previousVertex->getEdges()->end(),
				[currentId](std::pair<int, float>& p) { return p.first == currentId; });

			if (toCurrentPath == previousVertex->getEdges()->end())
			{
				(previousVertex->getEdges())->push_back(std::make_pair(currentId, -newFlow));
			}
			else
			{
				toCurrentPath->second -= newFlow;
			}
			
		}
		
	}

	return maxFLow;
}

std::vector<Vertex> Graph::getV()
{
	return v;
}

