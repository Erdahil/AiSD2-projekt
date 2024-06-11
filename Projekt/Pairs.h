#pragma once
#include "Carrier.h"

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
};

