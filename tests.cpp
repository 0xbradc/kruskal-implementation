#include "Graph.h"
#include <cstdint>
#include <iostream>
#include <iterator>
#include <vector>

const bool TIMER = true;    //"y" == std::getenv("TIMER");
const bool T_WEIGHT = true; //"y" == std::getenv("T_WEIGHT"); // TODO: set this to true before final turn in

using namespace std;

int main(int argc, char **argv)
{
    const int DIMENSION = atoi(argv[1]);
    const int TRIALS = atoi(argv[2]);
    GraphType type;
    const int NODES[12] = {/* 128, 256, 512, 1024, 2048, 4096, 8192, 16384, */ 32768, 65536, 131072, 262144};

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

    // print out csv header
    cout << "Nodes, Trial #, Rand Generation time, Sorting time, Kruskal time, Total MST Edge Weight" << endl;

    for (int x : NODES)
    {
        for (int t = 0; t < TRIALS; t++)
        {
            cout << x << ", " << t << ", ";
            clock_t timer = clock();
            Graph graph = Graph(type, x);

            timer = clock();
            float mst_weight = graph.kruskals();
            if (TIMER)
                cout /* << "Kruskal's time: " */ << ((double)(clock() - timer)) / CLOCKS_PER_SEC << ", " /* << endl */;
            if (T_WEIGHT)
                cout << /* "Total MST Edge Weight: " <<  */ mst_weight << endl;
        }
    }

    return 0;
}
