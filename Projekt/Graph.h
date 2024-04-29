#pragma once
#include "Vertex.h"

//w tym pliku sa deklaracje metod i zmiennych klasy Graph bez ich definicji

class Graph
{
private:
	int n; // liczba wierzcholkow
	std::vector<Vertex> v;
	int factory;

	std::vector< std::vector<int>> neighbours;

public:
	void generateGraph();//generuje graf
	void fixGeneratedGraph();
	void dfsForFix(int id, int groupid); // funkcja uzywana przez fixGeneratedGraph();
	int ifConnected(); // funkcja uzywana przez fixGeneratedGraph();
	void probaOutputu();//testowa
	void setn(int n);//do testow na razie tylko - idk czy bedzie potrzebne
	void outputGraph();
	void inputGraph();


	//std::vector<Vertex> getVerticesBFS(int endnode);
	//bool ifConnectedBFS();
	std::vector<Vertex> getShortestPathBFS(int endnode);

};

