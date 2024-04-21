#pragma once
#include <vector>
//#include <utility> //zawiera pair - mozliwe ze bedzie potrzebne przy szukaniu par - na razie nie robie tego

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

