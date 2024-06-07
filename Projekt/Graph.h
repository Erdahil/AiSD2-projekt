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
	std::string filePath = "Graph.txt";

	bool outpuGraphToFile();

public:
	//std::vector<Vertex> v; // zrobilam swapa narazie bo mnie cos wezmie zaraz, jestem zbyt glupia zeby ogarnac to jakos inazcej :33
	void generateGraph();//generuje graf
	void fixGeneratedGraph();
	void dfsForFix(int id, int groupid); // funkcja uzywana przez fixGeneratedGraph();
	int ifConnected(); // funkcja uzywana przez fixGeneratedGraph();
	void probaOutputu();//testowa
	void setn(int n);//do testow na razie tylko - idk czy bedzie potrzebne
	void outputGraph();
	void inputGraph();
	bool inputGraphFromFile();
	std::vector<Vertex> getV();

	void guardShedule(std::vector<Vertex> convexHull);


	//std::vector<Vertex> getVerticesBFS(int endnode);
	//bool ifConnectedBFS();
	std::vector<Vertex> getShortestPathBFS(int endnode);

	float maximumFlow(int endnodeId);
	void flowCleaner();

	void showFlow();//do testowania

};

