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

