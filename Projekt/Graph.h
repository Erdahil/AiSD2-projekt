#pragma once
#include "Vertex.h"

//w tym pliku sa deklaracje metod i zmiennych klasy Graph bez ich definicji

class Graph
{
private:
	int n; // liczba wierzcholkow
	std::vector<Vertex> v;
	int factory;
	std::string filePath = "Graph.txt";

	struct queueComparator //do kolejki potem potrzebny
	{
		bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2)
			const
		{
			return p1.second < p2.second;
		}
	};
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, queueComparator> guards;//kolejka stra¿ników <id, energia>


public:
	int getFactoryId();
	void generateGraph();//generuje graf
	void fixGeneratedGraph();
	void dfsForFix(int id, int groupid); // funkcja uzywana przez fixGeneratedGraph();
	int ifConnected(); // funkcja uzywana przez fixGeneratedGraph();
	void probaOutputu();//testowa
	void setn(int n);//do testow na razie tylko - idk czy bedzie potrzebne
	void outputGraph();
	void inputGraph();
	bool inputGraphFromFile();
	bool outpuGraphToFile();
	std::vector<Vertex> getV();

	void guardShedule(std::vector<Vertex> convexHull);
	void generateBrightness(std::vector<Vertex>* convexHull);
	void inputBrightness(std::vector<Vertex>* convexHull);

	void generateGuards(int maxSize);
	void inputGuards();
	void outputGuards();

	//std::vector<Vertex> getVerticesBFS(int endnode);
	//bool ifConnectedBFS();
	std::vector<Vertex> getShortestPathBFS(int endnode);

	float maximumFlow(int endnodeId);
	void flowCleaner();

	void showFlow();//do testowania

	void drawGraph();

};

