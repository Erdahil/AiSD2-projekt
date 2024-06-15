#pragma once
#include <vector>
#include "Vertex.h"

// klasa do tworzenia otoczki wypuk³ej za pomoc¹ algorytmu Jarvisa i obliczania jej obwodu

class ConvexHull 
{
private:
    static int crossProduct(Vertex p, Vertex q, Vertex r);
    static float distance(Vertex p, Vertex q);
public:
    static std::vector<Vertex> calculateConvexHull(std::vector<Vertex> v); // znajdowanie otoczki
    static float perimeter(std::vector<Vertex>& v);  // obliczanie obwodu otoczki
};
