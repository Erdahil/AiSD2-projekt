#include <iostream>
#include <algorithm>
#include <queue>
#include "Pairs.h"

void Pairs::generatePairs()
{

	std::cout << "Podaj ilosc tragarzy majacych rece skierowane w prawo" << std::endl;

	while (!(std::cin >> r) || !(r >= 0))
	{
		std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
		std::cout << "Niepoprawna wartoœæ. Wpisz jeszcze raz: ";
	}

	std::cout << "\n-----------------\n";

	std::cout << "Podaj ilosc tragarzy majacych rece skierowane w lewo" << std::endl;

	while (!(std::cin >> l) || !(l >= 0))
	{
		std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
		std::cout << "Niepoprawna wartoœæ. Wpisz jeszcze raz: ";
	}

	std::cout << "\n-----------------\n";


	carriers.resize(r + l);

	if (l == 0 || r == 0) return;

	for (int i = 0; i < l + r; i++)
	{
		carriers[i].setid(i);
		if (i < r) // losujemy ile wychodzi tylko dla tych z jednej strony
		{
			int randLikes = rand() % l;
			std::vector<std::pair<int, float>>* likes = carriers[i].getLikes();
			carriers[i].setNumberOfLikes(randLikes);
			carriers[i].getLikes()->resize(randLikes);
			std::vector<int> alreadyIn; // wektor do sprawdzania zeby nie bylo powtorek

			for (int j = 0; j < r + l; j++)
			{
				if (i == j)
				{
					alreadyIn.push_back(1);
				}
				else
				{
					alreadyIn.push_back(0);
				}
			}

			for (int j = 0; j < randLikes; j++)
			{
				int addingCarrierID = (rand() % l) + r;
				while (alreadyIn[addingCarrierID] == 1)
				{
					addingCarrierID = (rand() % l) + r;
				}
				alreadyIn[addingCarrierID] = 1;

				(*likes)[j].first = addingCarrierID;
				(*likes)[j].second = 1.0;
			}
		}
	}
}

void Pairs::inputPairs()
{
	std::cout << "Podaj ilosc tragarzy z rekami w prawo:\n";
	while (!(std::cin >> r) || r < 0)
	{
		std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
		std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
	}

	std::cout << "Podaj ilosc tragarzy z rekami w lewo:\n";
	while (!(std::cin >> l) || l < 0)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
	}

	std::cout << "Wczytywanie danych dla tragarzy z rekami w prawo!\nDla tych z rekami w lewo zostanie uzupelnione przez program\n";
	carriers.resize(l + r);

	if (l == 0 || r == 0) return;

	for (int i = 0; i < r; i++)
	{
		int numLikes;
		std::cout << "Podaj ilu tragarzy lubi tragarz o id " << i << ":\n";

		while (!(std::cin >> numLikes) || numLikes < 0 || numLikes > l)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
		}

		carriers[i].getLikes()->resize(numLikes);
		if (numLikes > 0)
		{
			std::cout << "Podaj id tych tragarzy, ktorych lubi (id musi byc w przedziale od 0 do " << l - 1 << " wlacznie ):\n";
			std::vector <int> contains;//do sprawdzenia czy ten juz byl podany
			for (int j = 0; j < numLikes; j++)
			{
				int newLike;
				while (!(std::cin >> newLike) || !((newLike += r) >= r && newLike < l + r))
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Bledne id; podaj jeszcze raz:\n";
				}

				while (std::find(contains.begin(), contains.end(), newLike) != contains.end())
				{
					std::cout << "To id bylo juz podane; podaj jeszcze raz:\n";
					std::cin >> newLike;
				}

				contains.push_back(newLike);

				(*carriers[i].getLikes())[j].first = newLike;
				(*carriers[i].getLikes())[j].second = 1.0;
			}
		}
	}
}

void Pairs::outputPairs()
{
	//std::cout << "-----------------\n";
	std::cout << "ilosc tragarzy majacych rece w prawo: " << r << '\n';
	std::cout << "ilosc tragarzy majacych rece w lewo: " << l << '\n';
	std::cout << "\n-----------------\n";
	std::cout << "kierunek transportu: \n";
	std::cout << "tragarze z rekami w prawo -> tragarze z rekami w lewo\n";
	std::cout << "\n-----------------\n";

	for (int i = 0; i < r; i++) // wypisuje tylko tych z rekami w prawo 
	{
		std::cout << "> id leworecznych tragarzy ktorych lubi tragarz praworeczny o id " << i << ":\n";
		if (carriers[i].getLikes()->empty())
		{
			std::cout << "zadnego";
		}
		else
		{
			for (int j = 0; j < carriers[i].getLikes()->size(); j++)
			{
				std::cout << (*carriers[i].getLikes())[j].first << ' '; //odejmowanie r daje bardziej czytelny wynik zgodny z systemem indeksowania wyswietlanym w inputPairs()
			}
		}

		std::cout << '\n';
	}
}

std::vector<Vertex> Pairs::getShortestPathBFS(int factory, int endnode, std::vector<Vertex>* v)
{
	int n = v->size();
	std::vector<Vertex> shortestPath;
	std::vector<int> previous(n, -1); // zbior poprzednikow
	std::vector<bool> visited(n, false);
	std::queue<int> line; // do bfsa - kolejka, do dfa - stos
	bool changed = false; // do sprawdzenia czy wektor intow 'previous' zostala zmodyfikowana jakos

	if (v->size() == 0)
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


		for (std::tuple<int, float, float> neighbour : (*(*v)[current].getEdges())) // przechodzimy po kolei po wszystkich elementach wektora edges danego wierzcholka
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
			shortestPath.push_back((*v)[i]);
		}
		shortestPath.push_back((*v)[factory]);
	}
	return shortestPath;
}

float Pairs::maximumFlow(int factory, int endnodeId, std::vector<Vertex>* v, std::vector<std::pair<int, int>>* examplePairs)
{
	float maxFlow = 0;
	float newFlow = FLT_MAX;
	Vertex endnode = (*v)[endnodeId];

	if (endnodeId == factory)
	{
		return 0;
	}
	//flowCleaner(v);

	std::vector<Vertex> path;


	while (true)
	{
		newFlow = FLT_MAX;
		path = getShortestPathBFS(factory, endnode.getid(), v);

		/*for (Vertex p : path)
		{
			std::cout << p.getid() << " ";
		}
		std::cout << std::endl;*/

		if (path.size() == 0) break;

		examplePairs->push_back(std::make_pair(path[2].getid(), path[1].getid()));

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
				(*v).begin(), (*v).end(),
				[&currentId](Vertex& p) { return p.getid() == currentId; });
			std::vector<Vertex>::iterator previousVertex = std::find_if(	//znajduje poprzednik wczesniejszego wierzcholka, mozna pominac jesli path zawieralby reference do wierzcholkow chyba
				(*v).begin(), (*v).end(),
				[&previousId](Vertex& p) { return p.getid() == previousId; });


			std::vector<std::tuple<int, float, float>>::iterator toPreviousPath = std::find_if( //znajduje odpowiednia droge wychodzaca z wierzcholka
				currentVertex->getEdges()->begin(), currentVertex->getEdges()->end(),
				[previousId](std::tuple<int, float, float>& p) { return std::get<0>(p) == previousId; });

			if (toPreviousPath != currentVertex->getEdges()->end())
			{
				std::get<2>(*toPreviousPath) -= newFlow;
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

//void Pairs::flowCleaner(std::vector<Vertex>* v)
//{
//	for (int i = 0; i < v->size(); i++)
//	{
//		for (int j = 0; j < (*v)[i].getEdges()->size(); j++)
//		{
//			std::get<2>((*(*v)[i].getEdges())[j]) = 0;
//		}
//	}
//}

void Pairs::connectingPairs()
{
	std::vector<Vertex> tmpV;
	int carriersCount = carriers.size();

	tmpV.resize(carriersCount + 2);
	tmpV[carriersCount].setid(carriersCount); //dodanie wierzcholka poczatkowego
	tmpV[carriersCount + 1].setid(carriersCount + 1); //dodanie wierzcholka koncowego

	std::vector<std::tuple<int, float, float>>* e = tmpV[carriersCount].getEdges();
	e->resize(r);

	for (int j = 0; j < r; j++) //polaczenie wierzcholka poczatkowego z praworecznymi tragarzami
	{
		std::get<0>((*e)[j]) = carriers[j].getid();
		std::get<1>((*e)[j]) = 1;
		std::get<2>((*e)[j]) = 0;
	}

	for (int i = 0; i < r; i++) //polaczenie kazdego z praworecznych tragarzy z tragarzmi ktorych lubi
	{
		std::vector<std::tuple<int, float, float>>* e = tmpV[i].getEdges();
		std::vector<std::pair<int, float>>* likes = carriers[i].getLikes();
		int numberOfLikes = carriers[i].getNumberOfLikes();

		e->resize(numberOfLikes);

		tmpV[i].setid(carriers[i].getid());

		for (int j = 0; j < numberOfLikes; j++)
		{
			std::get<0>((*e)[j]) = (*likes)[j].first;
			std::get<1>((*e)[j]) = 1;
			std::get<2>((*e)[j]) = 0;
		}
	}

	for (int i = r; i < l + r; i++)  //polaczenie leworecznych tragarzy z wierzcholkiem koncowym
	{
		std::vector<std::tuple<int, float, float>>* e = tmpV[i].getEdges();
		std::vector<std::pair<int, float>>* likes = carriers[i].getLikes();
		int numberOfLikes = carriers[i].getNumberOfLikes();

		e->resize(1);

		tmpV[i].setid(carriers[i].getid());
		std::get<0>((*e)[0]) = carriersCount + 1;
		std::get<1>((*e)[0]) = 1;
		std::get<2>((*e)[0]) = 0;
	}

	std::vector<std::pair<int, int>> examplePairs;

	std::cout << "\n-----------------\n";
	std::cout << "Maksymalna liczba par jakie mozna utworzyc: " << maximumFlow(carriersCount, carriersCount + 1, &tmpV, &examplePairs) << "\n";
	std::cout << "\nPrzykladowe pary tragarzy:\n";
	for (std::pair<int, int> p : examplePairs)
	{
		std::cout << p.first << " <--> " << p.second << "\n";
	}
}
