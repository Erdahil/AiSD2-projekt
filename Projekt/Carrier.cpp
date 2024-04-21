#include "Carrier.h"

std::vector<std::pair<int, float>>* Carrier::getLikes()
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