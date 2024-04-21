#pragma once
#include <vector>
#include <utility> //zawiera pair - mozliwe ze bedzie potrzebne przy szukaniu par - na razie nie robie tego

// pojedynczy tragarz

class Carrier
{
private:
	int id;
	int numberOfLikes;
	std::vector<std::pair<int, float>> likes;
public:
	std::vector<std::pair<int, float>>* getLikes();
	void setid(int id);
	void setNumberOfLikes(int l);
	int getid();
	int getNumberOfLikes();
};

