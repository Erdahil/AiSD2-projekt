#pragma once
#include <string>
#include "TreeNode.h"
#include <map>

class Melody
{
private:
	std::string s;//melodia
	std::string encrypted;
	std::string decrypted;
	int sSize; //d³ugoœæ melodii by nie robic potem ciagle s.size()
	TreeNode* root;//korzen drzewa do Huffmana
	std::map<char, std::string> mp;//mapa do kodowania Huffmana
	std::string mapTemp = ""; //pomocniczy do tworzenia kodow dla liter
public:
	void generateMelody(int len); // przyjmuje za argument dlugosc melodii
	void outputMelody();//proste wypisanie melodii
	void outputEncryptedMelody();//proste wypisanie zaszyfrowanej melodii
	void outputDecryptedMelody();//proste wypisanie rozszyfrowanej melodii
	void encryptHuffman();//zaszyfrowanie melodii algorytmem Huffmana
	void decryptHuffman();
	void makeHuffmanMap(TreeNode* temp); //pomocnicza rekurencyjna dla utworzenia mapy do zakodowania Huffmana;
	void setMelody(std::string s);
	void deleteHuffmanTree(TreeNode* del);//uzywane w destruktorze
	~Melody();
	std::string getMelody(); // do wyszukiwania wzorca
};

