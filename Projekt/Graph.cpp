#include <iostream>
#include <vector>
#include "Graph.h"

// deklaracje metod z klasy Graph

void Graph::generateGraph()
{
	srand(time(NULL));

	n = 3; //minimalna ilosc wierzcholkow maybe
	n+=rand()%10000; // liczba wierzcholkow [mniejsza od 10003 dla testow na razie]

}

void Graph::probaOutputu()
{
	std::cout << n;
}


