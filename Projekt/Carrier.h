#pragma once
#include <vector>
#include <utility> //zawiera pair

// pojedynczy tragarz

class Carrier
{
private:
	int id;
	int numberOfLikes;
	std::vector<int> likes;
public:
	std::vector<int>* getLikes();
	void setid(int id);
	void setNumberOfLikes(int l);
	int getid();
	int getNumberOfLikes();
};

