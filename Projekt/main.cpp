#include <iostream>
//#include <vector>
#include "Graph.h"
#include "Pairs.h"
#include "ConvexHull.h"
#include "Melody.h"
//using namespace std;

int main()
{
	//dk
	//ogarnalem 2
	//meow
	std::cout << "Hello World!\n"; //niech ktos to usunie pls
	std::cout << "Meow\n";

	int decision;
	std::cout << "Wybierz czy chcesz rozwiazac zadanie 1 [1], czy zadanie 2 [2]:\n";//dodalem by szybciej sprawdzac inne zadania - potem mozna zmienic forme

	while (!(std::cin >> decision) || !(decision == 1 || decision == 2))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Niepoprawny numer; podaj jeszcze raz:\n";
	}

	if (decision == 1)
	{
		char c;
		std::cout << "Wybierz czy chcesz wygenerowac graf [g], czy wprowadzic recznie [r]:\n";

		while (!(std::cin >> c) || !(c == 'g' || c == 'r'))
		{
			std::cin.clear();//czysci flagi bledow pojawiajace sie w cin, by dalej mozna bylo z niego korzystac
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//usuwa reszte znakow by nie wywolaly ponownie bledu
			std::cout << "Niepoprawne polecenie; podaj jeszcze raz:\n";
		}

		Graph g1;

		if (c == 'g')
		{
			g1.generateGraph();
			g1.fixGeneratedGraph();//sprawia ze graf staje sie drzewem o korzeniu w fabryce jesli nim nie byl
			g1.outputGraph();

			//g1.generateGraph();
			//g1.probaOutputu();
			/* testy
			g1.setn(10);
			g1.probaOutputu();
			*/
		}
		else if (c == 'r')
		{
			g1.inputGraph();
			g1.outputGraph();
		}

		std::cout << "\n-----------------\n";
		std::cout << "Wybierz czy chcesz wygenerowac pary tragarzy [g], czy wprowadzic recznie [r]:\n";

		while (!(std::cin >> c) || !(c == 'g' || c == 'r'))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Niepoprawne polecenie; podaj jeszcze raz:\n";
		}

		Pairs p1;

		if (c == 'g')
		{
			p1.generatePairs();
			p1.outputPairs();
		}
		else if (c == 'r')
		{
			p1.inputPairs();
			p1.outputPairs();
		}

		//testowanie funkcji do zwracania max przeplywu
		std::cout << "Czy chcesz sprawdziæ max przeplyw z fabryki do wierzcholka? t/n: ";
		std::cin >> c;

		if (c)
		{
			int id;
			std::cout << "Podaj id wierzcholka: ";
			std::cin >> id;
			std::cout << "Max przeplyw to : " << g1.maximumFlow(id) << "\n";
		}

		// testowanie otoczki zakomentowala, bo zeby ja testowac to w graph.h wektora przerzucilam z private na public

		// Obliczanie otoczki wypuk³ej dla grafu g1
		std::vector<Vertex> convexHull = ConvexHull::calculateConvexHull(g1.getV()); //usunalem tu z definicji funkcji & by dzialalo

		// Wyœwietlenie otoczki wypuk³ej
		std::cout << "Otoczka wypukla:\n";
		for (int i = 0; i < convexHull.size(); i++)
		{
			std::cout << "id wierzcholka: " << convexHull[i].getid() << ", x: " << convexHull[i].getx() << ", y: " << convexHull[i].gety() << std::endl;
		}
		std::cout << "obwod otoczki: " << ConvexHull::Perimeter(convexHull) << std::endl;

	}
	else if (decision == 2)
	{
		Melody m1;

		m1.generateMelody(20);
		//m1.setMelody("wcvglcmrxq");
		m1.outputMelody();
		m1.encryptHuffman();
	}


	return 0;
}