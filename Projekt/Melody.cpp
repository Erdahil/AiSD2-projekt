#include "Melody.h"
#include "TreeNode.h"
#include <iostream>
#include <queue>
#include <map>

struct QueueComparator//komparator do kolejki tak by pierwsze byly te z najmniejsza iloscia wystapien
{
	bool operator ()(TreeNode* const& tn1, TreeNode* const& tn2)
	{

		if (tn1->getn() > tn2->getn()) return true;

		if (tn1->getn() < tn2->getn()) return false;

		return false;
	}
};

void Melody::encryptHuffman()
{
	int t[26];
	for (int i = 0; i < 26; i++)//zerowanie tablicy
	{
		t[i] = 0;
	}

	for (int i = 0; i < sSize; i++)//liczenie 
	{
		t[s[i] - 'a']++;
	}


	std::priority_queue<TreeNode*, std::vector<TreeNode*>, QueueComparator> q;//tworzenie kolejki priorytertowej

	for (int i = 0; i < 26; i++)//wypelnienie q tak by zawierala jednowezlowe drzewa gdzie kazde jest od osobnej litery
	{
		if (t[i] != 0)
		{
			TreeNode* newTreeNode = new TreeNode();
			newTreeNode->setc((char)(i + 'a'));
			newTreeNode->setn(t[i]);
			newTreeNode->setLeft(nullptr);
			newTreeNode->setRight(nullptr);
			q.push(newTreeNode);
		}
	}
	if (s.size() == 1)
	{
		TreeNode* leftTN;
		leftTN = q.top();
		q.pop();

		TreeNode* newTN = new TreeNode();
		newTN->setc('-');
		newTN->setn(leftTN->getn());
		newTN->setLeft(leftTN);
		newTN->setRight(nullptr);
		q.push(newTN);
	}
	else
	{
		while (q.size() > 1) //laczenie drzew po dwa tak dlugo az bedzie jedno tylko
		{
			TreeNode* leftTN;
			leftTN = q.top();
			q.pop();

			TreeNode* rightTN;
			rightTN = q.top();
			q.pop();


			TreeNode* newTN = new TreeNode();
			newTN->setc('-');
			newTN->setn(leftTN->getn() + rightTN->getn());
			newTN->setLeft(leftTN);
			newTN->setRight(rightTN);
			q.push(newTN);
		}
	}

	root = q.top();

	makeHuffmanMap(root);//zapisanie liter z ich kodowaniami do map

	encrypted = "";

	for (int i = 0; i < sSize; i++)
	{
		encrypted += mp[s[i]];
	}

}

void Melody::makeHuffmanMap(TreeNode* temp)
{
	if (!temp) return;

	if (temp->getc() == '-')
	{
		mapTemp += '0';
		makeHuffmanMap(temp->getLeft());
		mapTemp += '1';
		makeHuffmanMap(temp->getRight());
	}
	else
	{
		mp[temp->getc()] = mapTemp;
	}

	if (mapTemp.size() > 0)//wykona siê raz wiêcej - bo te¿ dla pierwszego wêz³a na koniec jak string ju¿ jest pusty
	{
		mapTemp.pop_back();
	}

}

void Melody::decryptHuffman()
{
	TreeNode* current = root;
	decrypted = "";

	for (int i = 0; i < encrypted.size(); i++)
	{
		if (current->getc() != '-')
		{
			decrypted += current->getc();
			current = root;
		}
		if (encrypted[i] == '0')
		{
			current = current->getLeft();
		}
		else if (encrypted[i] == '1')
		{
			current = current->getRight();
		}

	}
	decrypted += current->getc();//¿eby ostatni¹ literê wpisa³o
}

void Melody::deleteHuffmanTree(TreeNode* del)//wywolywane potem w destruktorze klasy
{
	if (del)
	{
		deleteHuffmanTree(del->getLeft());
		deleteHuffmanTree(del->getRight());
		delete del;
	}
}

void Melody::generateMelody(int len)
{
	srand(time(NULL));

	for (int i = 0; i < len; i++)
	{
		s += (char)(rand() % 26 + 'a');
	}

	sSize = len;
}

void Melody::outputMelody()
{
	std::cout << "Melodia zapisana na stronie:\n";
	std::cout << s << '\n';
}

void Melody::outputEncryptedMelody()
{
	std::cout << "Melodia w postaci zaszyfrowanej:\n";
	std::cout << encrypted << '\n';
}

void Melody::outputDecryptedMelody()
{
	std::cout << "Melodia w postaci odszyfrowanej:\n";
	std::cout << decrypted << '\n';
}

void Melody::setMelody(std::string s)
{
	this->s = s;
	this->sSize = s.size();
}
std::string Melody::getMelody()
{
	return s;
}

Melody::~Melody()
{
	deleteHuffmanTree(root);
}