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
		int x = rand() % 20000 - 10000; //moga byc ujemne
		int y = rand() % 20000 - 10000;
		v[i].setCoords(x, y);
		v[i].setid(i);
	}

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

void Graph::inputGraph()
{
	std::cout << "Podaj ilosc wierzcholkow:\n";
	std::cin >> n;

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

	for (int i = 0; i < n; i++)
	{
		std::cout << "id wierzholka:" << i << '\n';
		std::cout << "x: " << v[i].getx() << " y: " << v[i].gety() << '\n';
		std::cout << "mozna do niego dojsc do: ";
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


