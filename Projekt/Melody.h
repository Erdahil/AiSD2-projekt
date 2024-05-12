#pragma once
#include <string>
#include "TreeNode.h"
#include <map>

class Melody
{
private:
	std::string s;
	int sSize; //rozmiar s by nie robic potem ciagle s.size()
	TreeNode* root;//korzen drzewa do Huffmana
	std::map<char, std::string> mp;//mapa do kodowania Huffmana
	std::string mapTemp = ""; //pomocniczy do tworzenia kodow dla liter
public:
	void generateMelody(int len); // przyjmuje za argument dlugosc melodii
	void outputMelody();//proste wypisanie melodii
	void encryptHuffman();//NIE DZIALA JESZCZE //zaszyfrowanie melodii algorytmem Huffmana
	void makeHuffmanMap(TreeNode* temp); //pomocnicza rekurencyjna dla utworzenia mapy do zakodowania Huffmana;
	void setMelody(std::string s);// dla testow Huffmana
	void deleteHuffmanTree(TreeNode* del);//trza w destruktorze potem to wywolac jak bedzie dzialalo wogle
	~Melody();
	void writeTree(TreeNode* del);
};

