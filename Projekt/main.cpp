#include <iostream>
#include <queue>
//#include <vector>
#include "Graph.h"
#include "Pairs.h"
#include "ConvexHull.h"
#include "Melody.h"
#include "PatternSearching.h"

int mainMenu();

int main()
{
	int decision;
	Graph g1;
	std::vector<Vertex> convexHull;
	bool graphLoaded = false;

	if (g1.inputGraphFromFile())
	{
		std::cout << "--------------------Wczytano graf--------------------\n";
		graphLoaded = true;
	}
	else
	{
		std::cout << "--------------------Nie udalo sie wczytac grafu--------------------\n";
	}

	std::cout << "\nNacisnij ENTER, by wrocic go glownego menu\n";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
	while (decision = mainMenu())
	{
		if (!graphLoaded && decision == 3)
		{
			std::cout << "Nie mozna stworzyc harmonogramu dla straznikow bez grafu!\n";

			std::cout << "\n\n-----------------\n";
			std::cout << "Nacisnij ENTER, by wrocic go glownego menu\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
			continue;
		}

		if (decision == 1)
		{
			int c;
			std::cout << "--------------------Graf--------------------\n";
			std::cout << "1.Generuj graf\n";
			std::cout << "2.Wprowadz graf recznie\n";
			std::cout << "3.Przejdz do zarzadzania tragarzami\n";
			std::cout << "4.Wroc do glownego menu\n";

			std::cout << "Podaj numer: ";

			while (!(std::cin >> c) || !(c >= 1 && c <= 4))
			{
				std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
				std::cout << "Niepoprawne polecenie; podaj jeszcze raz: ";
			}

			system("CLS");


			if (c == 1)
			{
				g1.generateGraph();
				g1.fixGeneratedGraph();//sprawia ze graf staje sie drzewem o korzeniu w fabryce jesli nim nie byl
				//g1.outputGraph();

				//g1.generateGraph();
				//g1.probaOutputu();
				/* testy
				g1.setn(10);
				g1.probaOutputu();
				*/
			}
			else if (c == 2)
			{
				std::cout << "-----------------Wprowadzanie grafu-----------------\n";
				g1.inputGraph();
				//g1.outputGraph();
			}
			else if (c == 4)
			{
				continue;
			}

			graphLoaded = true;
			system("CLS");

			std::cout << "-----------------Tragarze-----------------\n";
			std::cout << "1.Generuj pary tragarzy\n";
			std::cout << "2.Wprowadz pary tragarzy recznie\n";
			std::cout << "3.Wroc do glownego menu\n";

			std::cout << "Podaj numer: ";

			while (!(std::cin >> c) || !(c >= 1 && c <= 3))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Niepoprawne polecenie; podaj jeszcze raz: ";
			}

			Pairs p1;

			if (c == 1)
			{
				p1.generatePairs();
				//p1.outputPairs();
			}
			else if (c == 2)
			{
				std::cout << "-----------------Wprowadzanie tragarzy-----------------\n";
				p1.inputPairs();
				//p1.outputPairs();
			}
			else if (c == 3)
			{
				continue;
			}

			// Obliczanie otoczki wypuk³ej dla grafu g1
			convexHull = ConvexHull::calculateConvexHull(g1.getV()); //usunalem tu z definicji funkcji & by dzialalo

			system("CLS");

			std::cout << "-----------------Graf-----------------\n";
			g1.outputGraph();
			std::cout << "\n-----------------Tragarze-----------------\n";
			p1.outputPairs();

			// Wyœwietlenie otoczki wypuk³ej
			std::cout << "\n-----------------Otoczka wypukla-----------------\n";
			for (int i = 0; i < convexHull.size(); i++)
			{
				std::cout << "id wierzcholka: " << convexHull[i].getid() << ", x: " << convexHull[i].getx() << ", y: " << convexHull[i].gety() << std::endl;
			}
			std::cout << "obwod otoczki: " << ConvexHull::Perimeter(convexHull) << std::endl;

			
			std::cout << "\n-----------------Maksymlany przeplyw-----------------\n";
			for (int i = 0; i < convexHull.size(); i++)
			{
				int id = convexHull[i].getid();
				int flow = g1.maximumFlow(id);
				std::cout << "id wierzcholka: " << id << ", maksymalny przeplyw z fabryki: " << (flow == 0 ? 0 : flow) << "\n";
			}


			std::cout << "\n\n-----------------\n";
			std::cout << "Nacisnij ENTER, by wrocic do glownego menu\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();

		}
		else if (decision == 2)
		{
			Melody m1;
			int c;
			std::cout << "--------------------Melodia--------------------\n";
			std::cout << "1.Generuj melodie\n";
			std::cout << "2.Wprowadz melodie recznie\n";
			std::cout << "3.Wroc do glownego menu\n";
			std::cout << "Podaj numer: ";

			while (!(std::cin >> c) || !(c >= 1 && c <= 3))
			{
				std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
				std::cout << "Niepoprawne polecenie; podaj jeszcze raz: ";
			}

			system("CLS");

			if (c == 1)
			{
				std::cout << "--------------------Generacja melodii--------------------\n";
				int num;
				std::cout << "Podaj dlugosc melodii: ";
				while (!(std::cin >> num) || !(num > 0))
				{
					std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
					std::cout << "Niepoprawna liczba; podaj jeszcze raz: ";
				}
				m1.generateMelody(num);
			}
			else if (c == 2)
			{
				std::string tmpMel;
				std::cout << "-----------------Wprowadzanie melodii-----------------\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(std::cin, tmpMel);
				m1.setMelody(tmpMel);
			}
			else if (c == 3)
			{
				continue;
			}

			system("CLS");
			
			//m1.setMelody("wcvglcmrxq");
			//m1.setMelody("popopolimeowpoli"); // do testu wzorca

			std::cout << "-----------------Melodia-----------------\n";

			m1.outputMelody();
			std::cout << "-----------------\n";
			m1.encryptHuffman();
			m1.outputEncryptedMelody();
			std::cout << "-----------------\n";
			m1.decryptHuffman();
			m1.outputDecryptedMelody();
			std::cout << "-----------------\n";

			std::cout << "\n-----------------\n";
			std::cout << "Czy chcesz znalezc wzorze w zapisanej melodii?\n";
			std::cout << "1.Tak\n";
			std::cout << "2.Nie\n";

			while (true)
			{
				std::cout << "Podaj numer: ";
				while (!(std::cin >> c) || !(c >= 1 && c <= 2))
				{
					std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
					std::cout << "Niepoprawne polecenie; podaj jeszcze raz: ";
				}

				if (c == 1)
				{
					std::string pattern;
					PatternSearching ps;

					std::cout << "\nPodaj wzorzec do znalezienia:\n";
					std::cin >> pattern;

					ps.setPattern(pattern);
					std::vector<int> result = ps.search(m1.getMelody());
					if (result.empty())
					{
						std::cout << "nie znaleziono podanego wzorca" << std::endl;
					}
					else
					{
						std::cout << "indeks litery, w ktorej rozpoczyna sie wzorzec:" << std::endl;
						for (int i = 0; i < result.size(); i++)
						{
							std::cout << result[i] << std::endl;
						}
					}

					std::cout << "\n-----------------\n";
					std::cout << "Czy chcesz znalezc kolejny wzorze w zapisanej melodii?\n";
					std::cout << "1.Tak\n";
					std::cout << "2.Nie\n";
				}
				else if (c == 2) { break; }
			}
			
			
			std::cout << "\n\n-----------------\n";
			std::cout << "Nacisnij ENTER, by wrocic do glownego menu\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
		}
		else if (decision == 3)
		{
			int tempc;
			std::cout << "--------------------Jasnosc punktow na otoczce--------------------\n";
			std::cout << "1.Generuj jasnosc punktow\n";
			std::cout << "2.Wprowadz jasnosc punktow recznie\n";
			std::cout << "3.Wroc do glownego menu\n";
			std::cout << "Podaj numer: ";

			while (!(std::cin >> tempc) || !(tempc >= 1 && tempc <= 3))
			{
				std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
				std::cout << "Niepoprawne polecenie; podaj jeszcze raz: ";
			}

			system("CLS");

			if (tempc == 1)
			{
				g1.generateBrightness(&convexHull);
			}
			else if (tempc == 2)
			{
				std::cout << "-----------------Wprowadzanie jasnosci punktow-----------------\n";
				g1.inputBrightness(&convexHull);
			}
			else if (tempc == 3)
			{
				continue;
			}

			system("CLS");

			std::cout << "\n-----------------Jasnosc punktow na otoczce-----------------\n";
			for (int i = 0; i < convexHull.size(); i++)
			{
				std::cout << "id punktu: " << i << " jasnosc punktu: " << convexHull[i].getBrightness() << '\n';
			}

			std::cout << "\n\n--------------------Straznicy--------------------\n";
			std::cout << "1.Generuj straznikow\n";
			std::cout << "2.Wprowadz straznikow recznie\n";
			std::cout << "3.Wroc do glownego menu\n";
			std::cout << "Podaj numer: ";

			while (!(std::cin >> tempc) || !(tempc >= 1 && tempc <= 3))
			{
				std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
				std::cout << "Niepoprawne polecenie; podaj jeszcze raz: ";
			}

			//std::priority_queue<std::pair<int, int>, guardsComparator> guards;//kolejka straznikow - <id, energia>

			if (tempc == 1)
			{
				g1.generateGuards(convexHull.size());//domyslnie bedzie generowalo 20, idk mo¿na zmienic potem
			}
			else if (tempc == 2)
			{
				std::cout << "-----------------Wprowadzanie straznikow-----------------\n";
				g1.inputGuards();
			}
			else if (tempc == 3)
			{
				continue;
			}

			std::cout << "\n\n--------------------Straznicy--------------------\n";
			g1.outputGuards();//idk czy musi byc

			std::cout << "\n\n--------------------Harmonogram straznikow--------------------\n";
			g1.guardShedule(convexHull);

			std::cout << "\n\n-----------------\n";
			std::cout << "Nacisnij ENTER, by wrocic do glownego menu\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();

		}
		else if (decision == 4)
		{
			break;
		}
	}

	


	return 0;
}

int mainMenu()
{
	int decision;

	system("CLS");

	std::cout << "--------------------MENU--------------------\n";
	std::cout << "Ktory problem chcesz rozwiazac?\n";
	std::cout << "1.Zadanie 1\n";
	std::cout << "2.Zadanie 2\n";
	std::cout << "3.Zadanie 3\n";
	std::cout << "4.Wyjscie\n";

	std::cout << "Podaj numer: ";

	while (!(std::cin >> decision) || !(decision >= 1 && decision <= 4))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Niepoprawny numer; podaj jeszcze raz: ";
	}

	system("CLS");

	return decision;	
}