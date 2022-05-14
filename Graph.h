
#include "UnionFind.h"
#include <iostream>
#include <vector>

using namespace std;

#ifndef Edge
class Edge
{
public:
    float weight;
    pair<int, int> vertices;

    Edge();
    Edge(const Edge &e);
    Edge(float w, int u, int v);
};
#endif

#ifndef Node
struct Node
{
    float x;
    float y;
    float z;
    float t;

    Node(float x = 0, float y = 0, float z = 0, float t = 0);
};
#endif

#ifndef GraphType
enum GraphType
{
    RAND,
    UNIT_SQ,
    UNIT_CUBE,
    HYPERCUBE
};
#endif

#ifndef Graph

class Graph
{
private:
    int vertices;
    long long Vchoose2;
    vector<Edge> edges;

public:
    Graph(GraphType type, int V);

    void addEdge(float weight, int u, int v);

    void sortEdges();

    void print_graph();

    float kruskals();
};
#endif