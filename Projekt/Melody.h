#pragma once
#include <string>
#include "TreeNode.h"
#include <map>

class Melody
{
private:
	std::string s;//melodia
	std::string encrypted;
	std::string decrypted;//idk czy potrzebne - pewnie trza osobn¹ opcjê daæ i ... niech ktoœ mi przypomni o tym potem bym Dominikowi powiedzia³
	int sSize; //d³ugoœæ melodii by nie robic potem ciagle s.size()
	TreeNode* root;//korzen drzewa do Huffmana
	std::map<char, std::string> mp;//mapa do kodowania Huffmana
	std::string mapTemp = ""; //pomocniczy do tworzenia kodow dla liter
public:
	void generateMelody(int len); // przyjmuje za argument dlugosc melodii
	void outputMelody();//proste wypisanie melodii
	void outputEncryptedMelody();//proste wypisanie zaszyfrowanej melodii
	void outputDecryptedMelody();//proste wypisanie rozszyfrowanej melodii
	void encryptHuffman();//NIE DZIALA JESZCZE //zaszyfrowanie melodii algorytmem Huffmana
	void decryptHuffman();// - dok³adne u¿ycie tego potem do uzgodnienia
	void makeHuffmanMap(TreeNode* temp); //pomocnicza rekurencyjna dla utworzenia mapy do zakodowania Huffmana;
	void setMelody(std::string s);// dla testow Huffmana
	void deleteHuffmanTree(TreeNode* del);//trza w destruktorze potem to wywolac jak bedzie dzialalo wogle
	~Melody();
	void writeTree(TreeNode* del);
	std::string getMelody(); // do wyszukiwania wzorca
};

