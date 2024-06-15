#include "Vertex.h"

std::vector<std::tuple<int, float, float>>* Vertex::getEdges()
{
	return &edges;
}

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

void Vertex::setBrightness(int brightness)
{
	this->brightness = brightness;
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

int Vertex::getBrightness()
{
	return brightness;
}