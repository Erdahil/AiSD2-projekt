#include <iostream>
#include "Graph.h"


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
	}

	factory = rand() % n; // generacja polozenia fabryki;

	for (int i = 0; i < v.size(); i++)//generacja krawedzi z kazdego wierzcholka po kolei
	{
		std::vector<std::pair<int, float>>* e = v[i].getEdges();
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
			
			(*e)[j].first = addingVertID;
			//std::cout << (*e)[j].first << std::endl;
			(*e)[j].second = rand() % 10000 / 100.0; //losowanie przep³ywu
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
		if (v[(*v[id].getEdges())[i].first].getGroupid() == 0)
		{
			dfsForFix((*v[id].getEdges())[i].first, groupid);
		}
	}
}

void Graph::fixGeneratedGraph()
{
	int groupid = 1;
	dfsForFix(factory, groupid);

}

void Graph::inputGraph()
{
	std::cout << "Podaj ilosc wierzcholkow:\n";
	std::cin >> n;

	v.resize(n);
	for (int i = 0; i < v.size(); i++)//wpisanie wszystkich wierzcholkow
	{
		int x, y;
		std::cout << "Podaj koordynaty wierzcholka o id: " << i << '\n';
		std::cin >> x >> y;
		v[i].setCoords(x, y);
		v[i].setid(i);
		v[i].setGroupid(0);
	}

	for (int i = 0; i < v.size(); i++)//wpisanie krawedzi wychodzacych z wierzcholkow
	{
		int numberOfEdges;
		std::cout << "Podaj do ilu wierzcholkow mozna dojsc z wierzcholka o id: " << i << '\n';
		std::cin >> numberOfEdges;
		v[i].getEdges()->resize(numberOfEdges);
		std::cout << "Podaj id i maksymalny przeplyw krawedzi do tych wierzcholkow: \n";

		for (int j = 0; j < numberOfEdges; j++)
		{
			std::cin >> (*v[i].getEdges())[j].first >> (*v[i].getEdges())[j].second;
		}
		
	}
	std::cout << "Podaj id wierzcholka w ktorym jest fabryka: \n";
	std::cin >> factory;
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
		std::cout << "groupid wierzholka: " << v[i].getGroupid() << '\n';
		std::cout << "x: " << v[i].getx() << " y: " << v[i].gety() << '\n';
		std::cout << "mozna do niego dojsc do: |id(max przeplyw)| ";
		if (v[i].getEdges()->empty())
		{
			std::cout << "zadnego";
		}
		else
		{
			for (int j = 0; j < v[i].getEdges()->size(); j++)
			{
				std::cout << (*v[i].getEdges())[j].first << "(" << (*v[i].getEdges())[j].second << ") ";
			}
		}
		
		std::cout << '\n';
	}
}


