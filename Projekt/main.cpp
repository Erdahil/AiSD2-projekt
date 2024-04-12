#include <iostream>
#include <vector>
#include "Graph.h"
using namespace std;

int main()
{
    //dk
    //ogarnalem 2
    //meow
    cout << "Hello World!\n";
    cout << "Meow\n";

    char c;
    cout << "Wybierz czy chcesz wygenerowac graf [g], czy wprowadzic recznie [r]:\n";
    cin >> c;

    Graph g1;

    if (c == 'g')
    {
        g1.generateGraph();
        g1.probaOutputu();
    }
    else if (c == 'r')
    {

    }

    return 0;
}