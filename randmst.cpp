#include "Graph.h"
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

const bool TIMER = true;
const bool T_WEIGHT = true;

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        cout << "Usage: ./randmst.o <flag> <numpoints> <numtrials> <dimension>" << endl;
        exit(1);
    }
    const int FLAG = atoi(argv[1]);
    const int NUM_POINTS = atoi(argv[2]);
    const int NUM_TRIALS = atoi(argv[3]);
    const int DIMENSION = atoi(argv[4]);
    GraphType type;

    if (NUM_POINTS < 0 || NUM_POINTS > 262144)
    {
        cout << "Numpoints out of range [0, 262144]." << endl;
        exit(1);
    }
    switch (DIMENSION)
    {
    case 0:
    case 1:
        type = RAND;
        break;
    case 2:
        type = UNIT_SQ;
        break;
    case 3:
        type = UNIT_CUBE;
        break;
    case 4:
        type = HYPERCUBE;
        break;
    default:
        cout << "Dimension out of range [0, 4]." << endl;
        exit(1);
    }

    for (int i = 0; i < NUM_TRIALS; i++)
    {
        clock_t timer = clock();
        Graph graph = Graph(type, NUM_POINTS);

        timer = clock();
        float mst_weight = graph.kruskals();

        if (TIMER)
            cout << "Kruskal's time: " << ((double)(clock() - timer)) / CLOCKS_PER_SEC << endl;
        if (T_WEIGHT)
            cout << "Total MST Edge Weight: " << mst_weight << endl;
    }

    return 0;
}
