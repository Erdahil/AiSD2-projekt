#include <iostream>
#include<vector>
using namespace std;

//Nie testowany

int ek(int startNode, int endNode)
{
    int maxFlow = 0;
    vector<int> path(n); //lista wiezlow na sciezce zwracana z bfs, gdzie n to liczba wezlow w grafie

    int newFlow = 0;

    while (newFlow = bfs(startNode, endNode, path))
    {
        maxFlow += newFlow;

        int current = endNode;

        while (current != startNode)
        {
            int previous = path[currrent - 1];

            capacity[previous][current] -= newFlow;  //pojemnosc drog w grafie, uzywana w bfs
            capacity[current][previous] += newFlow;

            current = previous;
        }
    }

    return maxFlow;

}