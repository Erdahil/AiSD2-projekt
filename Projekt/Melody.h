#pragma once
#include <string>

class Melody
{
private:
	std::string s;
	int sSize; //rozmiar s by nie robic potem ciagle s.size()
public:
	void generateMelody(int len); // przyjmuje za argument dlugosc melodii
	void outputMelody();//proste wypisanie melodii
	void encryptHuffman();//NIE DZIALA JESZCZE //zaszyfrowanie melodii algorytmem Huffmana
};

