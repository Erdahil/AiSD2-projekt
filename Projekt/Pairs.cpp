#include <iostream>
#include <algorithm>
#include "Pairs.h"

void Pairs::generatePairs()
{
	srand(time(NULL)+1000); // +1000 zeby generowalo co innego niz przy grafie
	r = rand() % 10 + 1; // %10 bo dla testow tylko takie male - mozna wiecej, albo ustawic by sie podawalo ilosc przy wywolywaniu potem
	l = rand() % 10 + 1;

	carriers.resize(r + l);
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
	std::cin >> r;
	while (r < 0)
	{
		std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
		std::cin >> r;
	}
	std::cout << "Podaj ilosc tragarzy z rekami w lewo:\n";
	std::cin >> l;
	while (l < 0)
	{
		std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
		std::cin >> l;
	}

	std::cout << "Wczytywanie danych dla tragarzy z rekami w prawo!\nDla tych z rekami w lewo zostanie uzupelnione przez program\n";
	carriers.resize(l + r);
	for (int i = 0; i < r; i++)
	{
		int numLikes;
		std::cout << "Podaj ilu tragarzy ktorych lubi tragarz o id " << i << ":\n";
		std::cin >> numLikes;

		while (numLikes < 0 || numLikes > l)
		{
			std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
			std::cin >> numLikes;
		}

		carriers[i].getLikes()->resize(numLikes);
		if (numLikes > 0)
		{
			std::cout << "Podaj id tych tragarzy:\n";
			std::vector <int> contains;//do sprawdzenia czy ten juz byl podany
			for (int j = 0; j < numLikes; j++)
			{
				int newLike;
				std::cin >> newLike;
				while (!(newLike >= r && newLike < l + r))
				{
					std::cout << "Bledne id; podaj jeszcze raz:\n";
					std::cin >> newLike;
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
	std::cout << "-----------------\n";
	std::cout << "ilosc tragarzy majacych rece w prawo: " << r << '\n';
	std::cout << "ilosc tragarzy majacych rece w lewo: " << l << '\n';
	std::cout << "-----------------\n";
	std::cout << "kierunek transportu: \n";
	std::cout << "tragarze z rekami w prawo -> tragarze z rekami w lewo\n";
	std::cout << "-----------------\n";
	
	for (int i = 0; i < r; i++) // wypisuje tylko tych z rekami w prawo bo skoro testowe to po kiego mam pisac dodatkowe funkcje by czytalo w druga strone duh
	{
		std::cout << "id tragarzy ktorych lubi tragarz o id " << i << ":\n";
		if (carriers[i].getLikes()->empty())
		{
			std::cout << "zadnego";
		}
		else
		{
			for (int j = 0; j < carriers[i].getLikes()->size(); j++)
			{
				std::cout << (*carriers[i].getLikes())[j].first << ' ';
			}
		}

		std::cout << '\n';
	}
}