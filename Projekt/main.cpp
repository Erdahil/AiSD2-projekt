#include <iostream>
#include <vector>
#include "Graph.h"
//using namespace std;

int main()
{
    //dk
    //ogarnalem 2
    //meow
    std::cout << "Hello World!\n"; //niech ktos to usunie pls
    std::cout << "Meow\n";

    char c;
    std::cout << "Wybierz czy chcesz wygenerowac graf [g], czy wprowadzic recznie [r]:\n";
    std::cin >> c;

    Graph g1;

    if (c == 'g')
    {
        g1.generateGraph();
        g1.fixGeneratedGraph();//sprawia ze graf staje sie drzewem o korzeniu w fabryce jesli nim nie byl
        g1.outputGraph();
        
        //g1.generateGraph();
        //g1.probaOutputu();
        /* testy
        g1.setn(10);
        g1.probaOutputu();
        */
    }
    else if (c == 'r')
    {
        g1.inputGraph();
        g1.outputGraph();
    }

    return 0;
}