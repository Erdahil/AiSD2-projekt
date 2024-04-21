#include <iostream>
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
			std::vector<int>* likes = carriers[i].getLikes();
			carriers[i].setNumberOfLikes(randLikes);
			carriers[i].getLikes()->resize(randLikes);
			std::vector<int> alreadyIn;

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

				(*likes)[j] = addingCarrierID;
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
	std::cout << "kierunek: \n";
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
				std::cout << (*carriers[i].getLikes())[j] << ' ';
			}
		}

		std::cout << '\n';
	}
}
