#include "Melody.h"
#include "TreeNode.h"
#include <iostream>
#include <queue>
//#include <utility>

/*
struct TreeNode//niepotrzebe juz raczej - zostaje gdybym jednak potrzebowal
{
	TreeNode* left;
	TreeNode* right;
	char c; // litera albo '-' jesli to korzen drzewa w ktorym jest wiecej niz jeden element
	int n; //ilosc wystapien
};
*/
struct QueueComparator//komparator do kolejki tak by pierwsze byly te z najmniejsza iloscia wystapien
{
	//bool operator ()(const TreeNode& tn1, const TreeNode& tn2)
	bool operator ()(TreeNode* const& tn1, TreeNode* const& tn2)
	{
		//return tn1->n > 
		
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

	for (int i = 0; i < 26; i++)//testowe wyswietlenie ilosci liter
	{
		
		std::cout << "ilosc " << (char)(i + 'a') << ": " << t[i] << '\n';
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

	while (q.size() > 1) //laczenie drzew po dwa tak dlugo az bedzie jedno tylko
	{
		TreeNode* leftTN;
		leftTN = q.top();
		q.pop();

		TreeNode* rightTN;
		rightTN = q.top();
		q.pop();
		

		std::cout << "laczenie " << leftTN->getn() << " i " << rightTN->getn() << '\n';
		TreeNode* newTN = new TreeNode();
		newTN->setc('-');
		newTN->setn(leftTN->getn() + rightTN->getn());
		newTN->setLeft(leftTN);
		newTN->setRight(rightTN);
		q.push(newTN);
	}
	/*
	TreeNode* outputTN = q.top();
	std::cout<<outputTN->getn()<<'\n'<<outputTN->getLeft()->getn()<<" "<< outputTN->getRight()->getn()<<" tu koniec\n";

	delete outputTN;*/
	root = q.top();

	//std::cout << outputTN->getLeft()->getLeft()->getn() << " costampiszeee\n";
	//writeTree(q.top());
	//deleteHuffmanTree(q.top());
	//potem dokoncze //albo nie. Trudne to. i trza jeszcze destruktor napisac do ostatniego drzewa w kolejce

}

void Melody::deleteHuffmanTree(TreeNode* del)
{
	if (del)
	{
		std::cout << "l ";
		deleteHuffmanTree(del->getLeft());
		deleteHuffmanTree(del->getRight());
		std::cout << "r\n";
		delete del;
	}
	/*
	if (del->getLeft()!=nullptr)
	{
		std::cout << "l ";
		deleteHuffmanTree(del->getLeft());
		
		
	}
	if (del->getRight() != nullptr)
	{
		deleteHuffmanTree(del->getRight());
		std::cout << "r\n";
	}
	delete del;
	*/
}

void Melody::writeTree(TreeNode* del)//do testow tylko 
{
	/*
	if (del)
	{
		deleteHuffmanTree(del->getLeft());
		deleteHuffmanTree(del->getRight());
		std::cout << "thing\n";
	}*/

	if (del == NULL)
	{
		return;
	}
	writeTree(del->getLeft());
	writeTree(del->getRight());
	std::cout << del->getn()<<" ";

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

void Melody::setMelody(std::string s)
{
	this->s = s;
	this->sSize = s.size();
}

Melody::~Melody()
{
	
	//writeTree(root);
	//std::cout << "zrobilo write\n";
	deleteHuffmanTree(root);
	//std::cout << "drzewo usuniete z pamieci\n";
}