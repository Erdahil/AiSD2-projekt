#include <iostream>
#include <algorithm>
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
		v[i].setIsLeader(false);
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
				v[factory].getEdges()->push_back(std::make_pair(i, rand() % 10000 / 100.0)); // tworzenie nowej krawedzi od fabryki do wczesniej nieosiagalnej czesci grafu i losowanie przeplywu
			}
		}
	}
}

void Graph::inputGraph()
{
	std::cout << "Podaj ilosc wierzcholkow:\n";
	std::cin >> n;
	while (n < 0)
	{
		std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
		std::cin >> n;
	}

	v.resize(n);
	for (int i = 0; i < v.size(); i++)//wpisanie wszystkich wierzcholkow
	{
		int x, y;
		std::cout << "Podaj koordynaty wierzcholka o id: " << i << '\n';
		std::cin >> x >> y;
		v[i].setCoords(x, y);
		v[i].setid(i);
		v[i].setGroupid(0);
		v[i].setIsLeader(false);
	}

	for (int i = 0; i < v.size(); i++)//wpisanie krawedzi wychodzacych z wierzcholkow
	{
		int numberOfEdges;
		std::cout << "Podaj do ilu wierzcholkow mozna dojsc z wierzcholka o id: " << i << '\n';
		std::cin >> numberOfEdges;
		while (numberOfEdges > 0 && numberOfEdges < n)
		{
			std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
			std::cin >> numberOfEdges;
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
			std::cin >> tempID;

			while (tempID < 0 || tempID == i || tempID >= n)
			{
				std::cout << "Bledne id; podaj jeszcze raz:\n";
				std::cin >> tempID;
			}

			while (std::find(contains.begin(), contains.end(), tempID) != contains.end())
			{
				std::cout << "To id bylo juz podane; podaj jeszcze raz:\n";
				std::cin >> tempID;
			}
			
			contains.push_back(tempID);
			
			(*v[i].getEdges())[j].first = tempID;

			std::cout << "Podaj maksymalny przeplyw krawedzi laczacej te wierzcholki:\n";
			std::cin >> tempFlow;
			while (tempFlow < 0)
			{
				std::cout << "Niepoprawna wartosc; podaj jeszcze raz:\n";
				std::cin >> tempFlow;
			}
			(*v[i].getEdges())[j].second = tempFlow;

			//std::cin >> (*v[i].getEdges())[j].first >> (*v[i].getEdges())[j].second; // ze starej wersji bez sprawdzania poprawnosci inputu
		}
		
	}
	std::cout << "Podaj id wierzcholka w ktorym jest fabryka: \n";
	std::cin >> factory;
	while (factory < 0 || factory >= n)
	{
		std::cout << "Bledne id; podaj jeszcze raz:\n";
		std::cin >> factory;
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


