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
	for (int i = 0; i < r; i++)
	{
		int numLikes;
		std::cout << "Podaj ilu tragarzy ktorych lubi tragarz o id " << i << ":\n";

		while (!(std::cin >> numLikes) || numLikes < 0 || numLikes > l)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Niepoprawna ilosc; podaj jeszcze raz:\n";
		}

		carriers[i].getLikes()->resize(numLikes);
		if (numLikes > 0)
		{
			std::cout << "Podaj id tych tragarzy, ktorych lubi (musza byc z rekami skierowanymi w lewo od " << l << " do " << l + r - 1<<" wlacznie ):\n";
			std::vector <int> contains;//do sprawdzenia czy ten juz byl podany
			for (int j = 0; j < numLikes; j++)
			{
				int newLike;
				while (!(std::cin >> newLike) || !(newLike >= r && newLike < l + r))
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
