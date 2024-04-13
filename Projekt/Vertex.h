#pragma once
#include <vector>
#include <utility>

class Vertex
{
private:
	int id;
	int groupid; // potrzebne do generacji przydatnego grafu (spojnego z perspektywy fabryki, czyli chyba drzewa, ale idk)
	bool isLeader; // jak wyzej
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
	bool getIsLeader();
	int getGroupid();
	void setid(int id);
	void setGroupid(int groupid);
	void setIsLeader(bool isLeader);
};

