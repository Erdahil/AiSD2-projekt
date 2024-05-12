#pragma once
#include <string>
#include "TreeNode.h"

class Melody
{
private:
	std::string s;
	int sSize; //rozmiar s by nie robic potem ciagle s.size()
	TreeNode* root;
public:
	void generateMelody(int len); // przyjmuje za argument dlugosc melodii
	void outputMelody();//proste wypisanie melodii
	void encryptHuffman();//NIE DZIALA JESZCZE //zaszyfrowanie melodii algorytmem Huffmana
	void setMelody(std::string s);// dla testow Huffmana
	void deleteHuffmanTree(TreeNode* del);//trza w destruktorze potem to wywolac jak bedzie dzialalo wogle
	~Melody();
	void writeTree(TreeNode* del);
};

