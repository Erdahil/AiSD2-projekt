#pragma once
#include "Carrier.h"
#include "Vertex.h"

// klasa do tworzenia grafu tragarzy i szukania ich par

class Pairs
{
private:
	std::vector<Carrier> carriers;
	int r, l; // ilosc tragarzy z rekami w prawo/ w lewo [idziemy od tych co maja w prawo do tych co maja w lewo]
public:
	void generatePairs();
	void inputPairs();
	//void findPairs();
	void outputPairs();
	void connectingPairs();

	float maximumFlow(int factory, int endnodeId, std::vector<Vertex>* v, std::vector<std::pair<int, int>>* examplePairs);
	//void flowCleaner(std::vector<Vertex>* v);
	std::vector<Vertex> getShortestPathBFS(int factory, int endnode, std::vector<Vertex>* v);
};

