#pragma once

//chyba tylko gettery i settery tutaj beda potrzebne

class TreeNode
{
private:
	TreeNode* left;
	TreeNode* right;
	char c;// litera albo '-' jesli to korzen drzewa w ktorym jest wiecej niz jeden element
	int n;//ilosc wystapien
public:
	TreeNode* getLeft();
	TreeNode* getRight();
	char getc();
	int getn();
	void setLeft(TreeNode* left);
	void setRight(TreeNode* right);
	void setc(char c);
	void setn(int n);
};

