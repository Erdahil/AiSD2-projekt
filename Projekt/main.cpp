#include <iostream>
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

	if (g1.inputGraphFromFile())
	{
		std::cout << "--------------------Wczytano graf--------------------\n";
	}
	else
	{
		std::cout << "--------------------Nie udalo sie wczytac grafu--------------------\n";
	}

	std::cout << "Nacisnij (Chyba dwa razy, bo cos nie dziala) ENTER, by kontynuowac\n";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
	//system("pause");
		
	while (decision = mainMenu())
	{
		if (decision == 1)
		{
			int c;
			std::cout << "--------------------MENU--------------------\n";
			std::cout << "1.Generuj graf\n";
			std::cout << "2.Wprowadz graf recznie\n";
			std::cout << "3.Przejdz do zarzadzania tragarzami\n";
			std::cout << "4.Wroc do glownego menu\n";

			std::cout << "Podaj numer: ";

			while (!(std::cin >> c) || !(c >= 1 || c <= 3))
			{
				std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
				std::cout << "Niepoprawne polecenie; podaj jeszcze raz:\n";
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

			system("CLS");

			std::cout << "-----------------Wprowadzanie tragarzy-----------------\n";
			std::cout << "1.Generuj pary tragarzy\n";
			std::cout << "2.Wprowadz pary tragarzy recznie\n";
			std::cout << "3.Wroc do glownego menu\n";

			std::cout << "Podaj numer: ";

			while (!(std::cin >> c) || !(c >= 1 || c <= 3))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Niepoprawne polecenie; podaj jeszcze raz:\n";
			}

			Pairs p1;

			if (c == 1)
			{
				p1.generatePairs();
				p1.outputPairs();
			}
			else if (c == 2)
			{
				p1.inputPairs();
				p1.outputPairs();
			}
			else if (c == 3)
			{
				continue;
			}

			// Obliczanie otoczki wypukłej dla grafu g1
			std::vector<Vertex> convexHull = ConvexHull::calculateConvexHull(g1.getV()); //usunalem tu z definicji funkcji & by dzialalo

			system("CLS");

			std::cout << "-----------------Graf-----------------\n";
			g1.outputGraph();
			std::cout << "\n-----------------Tragarze-----------------\n";
			p1.outputPairs();

			// Wyświetlenie otoczki wypukłej
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
			std::cout << "Nacisnij ENTER, by wrocic go glownego menu\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();

		}
		else if (decision == 2)
		{
			Melody m1;

			m1.generateMelody(20);
			//m1.setMelody("wcvglcmrxq");
			//m1.setMelody("popopolimeowpoli"); // do testu wzorca
			m1.outputMelody();
			m1.encryptHuffman();

			std::string pattern = "poli";
			PatternSearching ps;
			ps.setPattern(pattern);
			std::vector<int> result = ps.search(m1.getMelody());

			std::cout << "indeks litery, w ktorej rozpoczyna sie wzorzec:" << std::endl;
			for (int i = 0; i < result.size(); i++)
			{
				std::cout << result[i] << std::endl;
			}
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

	while (!(std::cin >> decision) || !(decision >= 1 || decision <= 4))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Niepoprawny numer; podaj jeszcze raz:\n";
	}

	system("CLS");

	return decision;	
}