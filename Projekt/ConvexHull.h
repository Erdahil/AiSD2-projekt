#pragma once
#include <vector>
#include "Vertex.h"

// klasa do tworzenia otoczki wypuk³ej za pomoc¹ algorytmu Jarvisa i obliczania jej obwodu

class ConvexHull 
{
private:
    static int CrossProduct(Vertex p, Vertex q, Vertex r);
public:
    static std::vector<Vertex> calculateConvexHull(std::vector<Vertex>& v); // znajdowanie otoczki
    static float Perimeter(std::vector<Vertex>& v);  // obliczanie obwodu otoczki
};
