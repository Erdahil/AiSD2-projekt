#include "TreeNode.h"

TreeNode* TreeNode::getLeft()
{
	return left;
}

TreeNode* TreeNode::getRight()
{
	return right;
}

char TreeNode::getc()
{
	return c;
}

int TreeNode::getn()
{
	return n;
}

void TreeNode::setLeft(TreeNode* left)
{
	this->left = left;
}

void TreeNode::setRight(TreeNode* right)
{
	this->right = right;
}

void TreeNode::setc(char c)
{
	this->c = c;
}

void TreeNode::setn(int n)
{
	this->n = n;
}