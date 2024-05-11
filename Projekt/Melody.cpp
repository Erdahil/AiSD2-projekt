#include "Melody.h"
#include <iostream>
#include <queue>
#include <utility>

struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	char c;
};

void Melody::encryptHuffman()
{
	int t[26];
	for (int i = 0; i < 26; i++)
	{
		t[i] = 0;
	}

	for (int i = 0; i < sSize; i++)
	{
		t[s[i] - 'a']++;
	}
	//potem dokoncze

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
	std::cout << s;
}