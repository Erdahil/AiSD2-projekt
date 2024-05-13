#pragma once
#include <vector>
#include <utility>
#include <tuple>

class Vertex
{
private:
	int id;
	int groupid; // potrzebne do generacji przydatnego grafu (spojnego z perspektywy fabryki, czyli chyba drzewa, ale idk)
	bool isLeader; // jak wyzej
	float x;
	float y;
	std::vector<std::tuple<int, float, float>> edges; //id wierzcholkow do ktorych mozna dojsc z tego (id, max przeplyw, aktualny przeplyw)
public:
	void setCoords(float x, float y);
	std::vector<std::tuple<int, float, float>>* getEdges();
	float getx();
	float gety();
	int getid();
	bool getIsLeader();
	int getGroupid();
	void setid(int id);
	void setGroupid(int groupid);
	void setIsLeader(bool isLeader);
};

