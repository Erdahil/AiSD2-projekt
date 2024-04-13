#pragma once
#include <vector>
#include <utility>

class Vertex
{
private:
	int id;
	int groupid;
	float x;
	float y;
	std::vector<std::pair<int, float>> edges; //id wierzcholkow do ktorych mozna dojsc z tego
public:
	void setCoords(float x, float y);
	std::vector<std::pair<int, float>>* getEdges()
	{
		//std::vector<std::pair<int, float>>* e = edges;
		return &edges;
	}
	float getx();
	float gety();
	int getid();
	int getGroupid();
	void setid(int id);
	void setGroupid(int groupid);
};

