#include <iostream>
#include <vector>
#include <Graph.h>
#include <Vertex.h>
using namespace std;

//Nie testowany

int ek(Vertex startNode, Vertex endNode)
{
    int maxFlow = 0;
    std::vector<Vertex> path(n); //lista wiezlow na sciezce zwracana z bfs, gdzie n to liczba wezlow w grafie
    
    int newFlow = 0;
       
    bfs(startNode, endNode, path);

    while (newFlow = )
    {
        maxFlow += newFlow;

        Vertex current = endNode;

        while (current.getId() != startNode.getId())
        {
            Vertex previous = path[currrent.getId() - 1];

            (*current.getEdges())[previous].second -= newFlow;
            (*previous.getEdges())[current].second += newFlow;

            current = previous;
        }
    }

    return maxFlow;

}