#pragma once
#include "Vertex.h"

//w tym pliku sa deklaracje metod i zmiennych klasy Graph bez ich definicji

class Graph
{
private:
	int n; // liczba wierzcholkow
	std::vector<Vertex> v;

public:
	void generateGraph();
	void probaOutputu();
	void setn(int n);//do testow na razie tylko - idk czy bedzie potrzebne
	void outputGraph();
};

