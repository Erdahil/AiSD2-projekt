#include "Melody.h"
#include <iostream>
#include <queue>
//#include <utility>

struct TreeNode//wezel drzewa - chyba bede musial to przeniesc do osobnej klasyyy killmeeeee
{
	TreeNode* left;
	TreeNode* right;
	char c; // litera albo '-' jesli to korzen drzewa w ktorym jest wiecej niz jeden element
	int n; //ilosc wystapien
};

struct QueueComparator//komparator do kolejki tak by pierwsze byly te z najmniejsza iloscia wystapien
{
	//bool operator ()(const TreeNode& tn1, const TreeNode& tn2)
	bool operator ()(TreeNode* const& tn1, TreeNode* const& tn2)
	{
		//return tn1->n > 
		
		if (tn1->n > tn2->n) return true;

		if (tn1->n < tn2->n) return false;

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

	for (int i = 0; i < 26; i++)//wypenienie q tak by zawierala jednowezlowe drzewa gdzie kazde jest od osobnej litery
	{
		if (t[i] != 0)
		{
			TreeNode* newTreeNode = new TreeNode();
			newTreeNode->c = (char)(i + 'a');
			newTreeNode->n = t[i];
			newTreeNode->left = nullptr;
			newTreeNode->right = nullptr;
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
		

		std::cout << "laczenie " << leftTN->n << " i " << rightTN->n << '\n';
		TreeNode* newTN = new TreeNode();
		newTN->c = '-';
		newTN->n = leftTN->n + rightTN->n;
		newTN->left = leftTN;
		newTN->right = rightTN;
		q.push(newTN);
	}

	TreeNode* outputTN = q.top();
	std::cout<<outputTN->n<<'\n';

	//potem dokoncze //albo nie. Trudne to. i trza jeszcze destruktor napisac do ostatniego drzewa w kolejce

}

void Melody::deleteHuffmanTree()
{

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
}