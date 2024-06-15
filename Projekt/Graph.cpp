#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
#include <fstream>
#include "Graph.h"
#include "Vertex.h"


// deklaracje metod z klasy Graph



void Graph::generateGraph()
{
	srand(time(NULL));

	std::cout << "Podaj ilosc wierzcholkow do wygenerowania" << std::endl;

	while (!(std::cin >> n) || !(n >= 3))
	{
		std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
		std::cout << "Niepoprawna wartoœæ. Wpisz jeszcze raz: ";
	}

	std::cout << "\n-----------------\n";

	v.resize(n);
	for (int i = 0; i < v.size(); i++)//generacja wszystkich wierzcholkow
	{
		float x = (rand() % 20000 - 10000) / 1000.0; //moga byc ujemne
		float y = (rand() % 20000 - 10000) / 1000.0;
		v[i].setCoords(x, y);
		v[i].setid(i);
		v[i].setGroupid(0);
		v[i].setIsLeader(false);
	}

	factory = rand() % n; // generacja polozenia fabryki;

	for (int i = 0; i < v.size(); i++)//generacja krawedzi z kazdego wierzcholka po kolei
	{
		std::vector<std::tuple<int, float, float>>* e = v[i].getEdges();
		//int numberOfEdges = (n <= 1 ? 0 : (rand() % (n - 1)) % 5); //losowanie ilosci krawedzi idacych z tego wierzcholka
		int numberOfEdges =rand() % (n - 1) % 5; //losowanie ilosci krawedzi idacych z tego wierzcholka

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


		for (int j = 0; j < numberOfEdges; j++)
		{
			int addingVertID = rand() % n;
			while (alreadyIn[addingVertID] == 1)
			{
				addingVertID = rand() % n;
			}
			alreadyIn[addingVertID] = 1;

			std::get<0>((*e)[j]) = addingVertID;
			std::get<1>((*e)[j]) = rand() % 10000 / 100.0; //losowanie przep³ywu
			std::get<2>((*e)[j]) = 0; // ustawienie aktualnego przeplywu na 0
		}
	}

	system("CLS");


	std::cout << "Czy chcesz zapisac graf?\n";
	std::cout << "1.Tak\n";
	std::cout << "2.Nie\n";

	int dec;

	while (!(std::cin >> dec) || !(dec >= 1 || dec <= 2))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Niepoprawne polecenie; podaj jeszcze raz:\n";
	}

	if (dec == 2)
	{
		return;
	}

	if (outpuGraphToFile())
	{
		std::cout << "Zapisano graf\n";
	}
	else
	{
		std::cout << "Nie udalo sie zapisac grafu\n";
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

			while (true)
			{
				while (!(std::cin >> tempID) || tempID < 0 || tempID == i || tempID >= n)
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Bledne id; podaj jeszcze raz:\n";
				}

				if (std::find(contains.begin(), contains.end(), tempID) != contains.end())
				{
					std::cout << "To id bylo juz podane; podaj jeszcze raz:\n";
				}
				else
				{
					break;
				}
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


	std::cout << "Czy chcesz zapisac graf?\n";
	std::cout << "1.Tak\n";
	std::cout << "1.Nie\n";

	int dec;

	while (!(std::cin >> dec) || !(dec >= 1 || dec <= 2))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Niepoprawne polecenie; podaj jeszcze raz:\n";
	}

	if (dec == 2)
	{
		return;
	}

	if (outpuGraphToFile())
	{
		std::cout << "Zapisano graf\n";
	}
	else
	{
		std::cout << "Nie udalo sie zapisac grafu\n";
	}
}

bool Graph::inputGraphFromFile()
{
	std::ifstream inputFile(filePath);

	if (!inputFile.is_open()) 
	{
		return false;
	}

	if (!(inputFile >> n) || n < 0)
	{
		std::cin.clear(); //czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
		return false;
	}

	v.resize(n);


	for (int i = 0; i < v.size(); i++)//wpisanie wszystkich wierzcholkow
	{
		float x, y;

		if (!(inputFile >> x >> y))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
		v[i].setCoords(x, y);
		v[i].setid(i);
		v[i].setGroupid(0);
		v[i].setIsLeader(false);

	}


	for (int i = 0; i < v.size(); i++)//wpisanie krawedzi wychodzacych z wierzcholkow
	{
		int numberOfEdges;


		if (!(inputFile >> numberOfEdges) || !(numberOfEdges >= 0 && numberOfEdges < n))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}

		v[i].getEdges()->resize(numberOfEdges);

		std::vector <int> contains; //do sprawdzenia czy ten juz byl podany

		for (int j = 0; j < numberOfEdges; j++)
		{
			int tempID;
			float tempFlow;


			if (!(inputFile >> tempID) || tempID < 0 || tempID == i || tempID >= n)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}

			if (std::find(contains.begin(), contains.end(), tempID) != contains.end())
			{
				return false;
			}

			contains.push_back(tempID);

			std::get<0>((*v[i].getEdges())[j]) = tempID;

			if (!(inputFile >> tempFlow) || tempFlow < 0)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				return false;
			}
			std::get<1>((*v[i].getEdges())[j]) = tempFlow;

			//std::cin >> (*v[i].getEdges())[j].first >> (*v[i].getEdges())[j].second; // ze starej wersji bez sprawdzania poprawnosci inputu
		}

	}


	if (!(inputFile >> factory) || factory < 0 || factory >= n)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}

	inputFile.close();

	return true;
}

bool Graph::outpuGraphToFile()
{
	std::ofstream outputFile(filePath);

	if (!inputFile.is_open()) 
	{
		return false;
	}

	if (!(outputFile << n << std::endl))
	{
		return false;
	}

	for (int i = 0; i < v.size(); i++)//wpisanie wszystkich wierzcholkow
	{
		if (!(outputFile << v[i].getx() << " " << v[i].gety() << std::endl))
		{
			return false;
		}
	}

	for (int i = 0; i < v.size(); i++)//wpisanie krawedzi wychodzacych z wierzcholkow
	{
		int numberOfEdges = v[i].getEdges()->size();
		if (!(outputFile << numberOfEdges << std::endl))
		{
			return false;
		}

		for (int j = 0; j < numberOfEdges; j++)
		{
			int tempID = std::get<0>((*v[i].getEdges())[j]);
			float tempFlow = std::get<1>((*v[i].getEdges())[j]);


			if (!(outputFile << tempID << " " << tempFlow << std::endl))
			{
				return false;
			}
		}

	}

	if (!(outputFile << factory))
	{
		return false;
	}

	outputFile.close();

	return true;

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
		std::cout << "id wierzcholka: " << i << '\n';
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
	std::queue<int> line; // do bfsa - kolejka, do dfa - stos
	bool changed = false; // do sprawdzenia czy wektor intow 'previous' zostala zmodyfikowana jakos

	if (v.size() == 0)
	{
		return shortestPath; // pusty wektor, nwm czy nie lepiej wtedy -1, burza mozgow jest potrzebna
	}

	line.push(factory);
	visited[factory] = true; // odwiedzamy fabryke jako pierwsza

	while (!line.empty())
	{
		int current = line.front(); // bedziemy walczyc z pierwszym elementem kolejki
		line.pop();


		if (current == endnode)
		{
			changed = true;
			break;
		}// jesli dotrzemy do ostatniego to znaczy, ze nie musimy juz dalej szukac


		for (std::tuple<int, float, float> neighbour : (*v[current].getEdges())) // przechodzimy po kolei po wszystkich elementach wektora edges danego wierzcholka
		{
			if (!visited[std::get<0>(neighbour)] && std::get<2>(neighbour) < std::get<1>(neighbour))
			{
				visited[std::get<0>(neighbour)] = true;
				previous[std::get<0>(neighbour)] = current; // ustawia aktualnie rozpatrywany wierzcholek jako "poprzednik" wybranego sasiada

				line.push(std::get<0>(neighbour));
			}
		}
	}

	if (changed)
	{
		for (int i = endnode; i != factory; i = previous[i])
		{
			shortestPath.push_back(v[i]);
		}
		shortestPath.push_back(v[factory]);
	}
	return shortestPath;
}


float Graph::maximumFlow(int endnodeId)
{
	float maxFlow = 0;
	float newFlow = FLT_MAX;
	Vertex endnode = v[endnodeId];

	if (endnodeId == factory)
	{
		return 0;
	}
	flowCleaner();

	std::vector<Vertex> path;


	while (true)
	{
		newFlow = FLT_MAX;
		path = getShortestPathBFS(endnode.getid());

		/*for (Vertex p : path) //wyswietlanie drogi
		{
			std::cout << p.getid() << " ";
		}
		std::cout << std::endl;*/

		if (path.size() == 0) break;

		for (int i = path.size() - 1; i > 0; i--) //szuka najmniejszej przepustowosci na sciezce
		{
			int key = path[i - 1].getid();

			std::vector<std::tuple<int, float, float>>::iterator it = std::find_if(
				path[i].getEdges()->begin(), path[i].getEdges()->end(),
				[&key](std::tuple<int, float, float>& p) { return std::get<0>(p) == key; }); //zwraca pare, gdzie kluczem jest nastepny wierzcholek


			if (newFlow > (std::get<1>(*it) - std::get<2>(*it)))
			{
				newFlow = (std::get<1>(*it) - std::get<2>(*it));
			}

		}


		if (newFlow <= 0) break;

		maxFlow += newFlow;


		for (int i = 0; i < path.size() - 1; i++)
		{
			int currentId = path[i].getid();
			int previousId = path[i + 1].getid();


			std::vector<Vertex>::iterator currentVertex = std::find_if(	//znajduje pierwszy wierzcholek, mozna pominac jesli path zawieralby reference do wierzcholkow chyba
				v.begin(), v.end(),
				[&currentId](Vertex& p) { return p.getid() == currentId; });
			std::vector<Vertex>::iterator previousVertex = std::find_if(	//znajduje poprzednika wczesniejszego wierzcholka, mozna pominac jesli path zawieralby reference do wierzcholkow chyba
				v.begin(), v.end(),
				[&previousId](Vertex& p) { return p.getid() == previousId; });


			std::vector<std::tuple<int, float, float>>::iterator toPreviousPath = std::find_if( //znajduje odpowiednia droge wychodzaca z wierzcholka
				currentVertex->getEdges()->begin(), currentVertex->getEdges()->end(),
				[previousId](std::tuple<int, float, float>& p) { return std::get<0>(p) == previousId; });

			if (toPreviousPath != currentVertex->getEdges()->end())
			{
				std::get<2>(*toPreviousPath) -= newFlow;
			}
			else
			{
				v[currentId].getEdges()->push_back(std::make_tuple(previousId, 0, -newFlow));
			}


			std::vector<std::tuple<int, float, float>>::iterator toCurrentPath = std::find_if( //znajduje odpowiednia droge wchodzaca do wierzcholka
				previousVertex->getEdges()->begin(), previousVertex->getEdges()->end(),
				[currentId](std::tuple<int, float, float>& p) { return std::get<0>(p) == currentId; });


			if (toCurrentPath != previousVertex->getEdges()->end())
			{
				std::get<2>(*toCurrentPath) += newFlow;
			}

		}

	}

	return maxFlow;
}

void Graph::flowCleaner()
{
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].getEdges()->size(); j++)
		{
			std::get<2>((*v[i].getEdges())[j]) = 0;
		}
	}
}

void Graph::showFlow()
{
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].getEdges()->size(); j++)
		{
			std::cout << std::get<2>((*v[i].getEdges())[j]);
		}
	}
}

void Graph::guardShedule(std::vector<Vertex> convexHull)
{
	int startId = 0;//szukanie maksymalnej jasnosci by od niej zaczynac

	for (int i = 0; i < convexHull.size(); i++)
	{
		if (convexHull[i].getBrightness() > convexHull[startId].getBrightness())
		{
			startId = i;
		}
	}

	for (int i = 0; i < startId; i++)
	{
		Vertex temp;
		temp = convexHull[0];
		convexHull.erase(convexHull.begin());
		convexHull.push_back(temp);
	}

	std::cout << "Straznicy beda zaczynac od puktu o id: " << startId << '\n';

	/*
	std::cout << guards.top().second;
	guards.pop();
	std::cout << guards.top().second;
	guards.pop();
	std::cout << guards.top().second;*/

	for (int i = 0; i < 7; i++)//dla kazdego dnia tygodnia trza znalezc
	{
		int currentEnergy = guards.top().second;

		int currentV = 0;
		int currentBrightness = convexHull[0].getBrightness();
		int rests = 0;

		while (currentV + currentEnergy < convexHull.size())
		{

			std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, queueComparator> currentlyConsidered; //<id, jasnosc> wierzcholkow do ktorych mozna dojsc

			for (int j = 1; j <= currentEnergy; j++)//utworzenie kolejki tych do ktorych mozna dojsc
			{
				currentlyConsidered.push(std::make_pair(currentV + j, convexHull[currentV + j].getBrightness()));
			}
			std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, queueComparator> consideredIfBrighter = currentlyConsidered;

			//std::cout << "na topie w kolejce: " << currentlyConsidered.top().first << '\n';//do zakomentowania
			bool empty = true;

			//currentV = currentlyConsidered.top().first;
			//currentBrightness = currentlyConsidered.top().second;
			int oldBrightness = currentBrightness;
			bool emptyTemp = false;

			while (empty)
			{
				//std::cout << "std\n";
				if (currentlyConsidered.top().second >= currentBrightness)//jesli obecny w kolejce jest jaœniejszy
				{

					currentlyConsidered.pop();
					if (currentlyConsidered.empty())
					{
						empty = false;
						emptyTemp = true;
						currentV += currentEnergy;
						currentBrightness = convexHull[currentV].getBrightness(); //jeœli wszystkie w kolejce s¹ jaœniesze to idziemy do ostatniego do którego mo¿emy dojœæ
					}
				}
				else
				{
					empty = false;
					currentV = currentlyConsidered.top().first;
					currentBrightness = currentlyConsidered.top().second;
				}
			}

			if (oldBrightness <= currentBrightness || emptyTemp)//jesli ten w ktorym jest, nie jest jasniejszy
			{
				rests++;
				//std::cout << currentV << '\n';
			}
		}

		std::cout << "Dla dnia tygodnia nr: " << i + 1 << " przydzielono straznika o id: " << guards.top().first << ". Musi on odpoczac " << rests + 1 << " raz(y).\n";

		guards.pop();
	}

}

void Graph::generateGuards(int maxSize)
{
	srand(time(NULL));
	for (int i = 0; i < 20; i++)//na razie 20, idk mozna zmienic
	{
		guards.push(std::make_pair(i, 1 + (rand() % 3)));//zeby maksymalnie mieli tyle energii ile jest w otoczce wierzcholkow
	}
}

void Graph::inputGuards()
{
	std::cout << "Podaj ilu straznikow chcesz wygenerowac: \n";
	int numbOfGuards;
	std::cin >> numbOfGuards;
	while (numbOfGuards < 7)
	{
		std::cout << "Zbyt malo by sporzadzic grafik pracy na caly tydzien.\nPodaj nowa ilosc:\n";
		std::cin >> numbOfGuards;
	}
	for (int i = 0; i < numbOfGuards; i++)
	{
		std::cout << "Podaj energie straznika o id: " << i << '\n';
		int energy;
		std::cin >> energy;
		while (energy < 1)
		{
			std::cout << "Niepoprawna ilosc energii\nPodaj nowa wartosc:\n";
			std::cin >> energy;
		}
		guards.push(std::make_pair(i, energy));
	}
}

void Graph::generateBrightness(std::vector<Vertex>* convexHull)
{
	srand(time(NULL));

	int max = (*convexHull).size();
	for (int i = 0; i < (*convexHull).size(); i++)
	{
		(*convexHull)[i].setBrightness(rand() % max);//zeby wygenerowana jasnosc nie byla wieksza od ilosci elementow - to tam nie ma znaczenia i tak i jakos sie lepiej ograniczmy po prostu
	}
}

void Graph::inputBrightness(std::vector<Vertex>* convexHull)
{
	for (int i = 0; i < (*convexHull).size(); i++)
	{
		int input;
		std::cout << "Wprowadz jasnosc dla punktu otoczki numer " << i << " o wspolrzednych:\n";//idk czy tu trza wspolrzedne robic
		std::cout << "x: " << (*convexHull)[i].getx() << '\n';
		std::cout << "y: " << (*convexHull)[i].gety() << '\n';
		std::cin >> input;
		(*convexHull)[i].setBrightness(input);
	}
}

void Graph::outputGuards()
{
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, queueComparator> copyGuards = guards;
	std::cout << "Dostepni straznicy:\n";

	while (!copyGuards.empty())
	{
		std::cout << "id: " << copyGuards.top().first << " energia: " << copyGuards.top().second << '\n';
		copyGuards.pop();
	}
	std::cout << '\n';
}

std::vector<Vertex> Graph::getV()
{
	return v;
}

int Graph::getFactoryId()
{
	return factory;
}

//void Graph::drawGraph()
//{
//	std::ofstream file("./rysunek.dot");
//
//	if (!file) {
//		std::cerr << "Blad otwarcia pliku " << std::endl;
//		return;
//	}
//
//	for (int i = 0; i < n; i++)
//	{
//		file << "digraph G {\n";
//		file << "	" << i << " [pos=\"" << v[i].getx() << "," << v[i].gety() << "!\", label=\"" << i << "\", color = \"" << (i == factory ? "red" : "blue") << "\"];\n";
//	}
//	file << "	\n";
//	for (int i = 0; i < n; i++)
//	{
//		std::vector<std::tuple<int, float, float>>* e = v[i].getEdges();
//
//		for (int j = 0; j < e->size(); j++)
//		{
//			file << "	" << i << "->" << j << "label=\"" << std::get<1>((*e)[j]) << "\"" << "\"];\n";
//		}
//	}
//	file << "}\n";
//
//	file.close();
//	system("dot -Tpng rysunek.dot -o rysunek.png");
//
//	system("rysunek.png");
//
//}
void Graph::drawGraph()
{
	std::ofstream file("./rysunek.dot");

	if (!file) {
		std::cerr << "Blad otwarcia pliku " << std::endl;
		return;
	}

	std::string color = "blue";

	file << "digraph G {\n";

	for (int i = 0; i < n; i++)
	{
		file << "    " << i << " [pos=\"" << v[i].getx() << "," << v[i].gety() << "!\", label=\"" << i << "\", color=\"" << (i == factory ? "red" : "blue") << "\"];\n";
	}


	for (int i = 0; i < n; i++)
	{
		std::vector<std::tuple<int, float, float>>* e = v[i].getEdges();

		for (int j = 0; j < e->size(); j++)
		{
			if (std::get<1>((*e)[j]) != 0)
			{
				file << "    " << i << " -> " << std::get<0>((*e)[j]) << " [label=\"" << std::get<1>((*e)[j]) << "\"];\n";
			}
		}
	}


	file << "}\n";

	file.close();

	system("neato -Kfdp -n -Tpng rysunek.dot -o rysunek.png");

	system("rysunek.png");

}

