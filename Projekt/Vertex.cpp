#include "Vertex.h"

void Vertex::setCoords(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vertex::setid(int id)
{
	this->id = id;
}

void Vertex::setGroupid(int groupid)
{
	this->groupid = groupid;
}

void Vertex::setIsLeader(bool isLeader)
{
	this->isLeader = isLeader;
}

float Vertex::getx()
{
	return x;
}

float Vertex::gety()
{
	return y;
}

int Vertex::getid()
{
	return id;
}

int Vertex::getGroupid()
{
	return groupid;
}

bool Vertex::getIsLeader()
{
	return isLeader;
}