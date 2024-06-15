#include "Carrier.h"

std::vector<int>* Carrier::getLikes()
{
	return &likes;
}

void Carrier::setid(int id)
{
	this->id = id;
}

void Carrier::setNumberOfLikes(int l)
{
	this->numberOfLikes = l;
}

int Carrier::getid()
{
	return id;
}

int Carrier::getNumberOfLikes()
{
	return numberOfLikes;
}