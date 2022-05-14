#include "Graph.h"
#include <iostream>
#include <ostream>
#include <vector>
#include <execution>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <random>

using namespace std;

const bool TIMER = true;
const bool G_WEIGHT = false;

Edge::Edge(const Edge &e)
{
    this->weight = e.weight;
    this->vertices = e.vertices;
};
Edge::Edge()
{
    this->weight = 0;
    this->vertices = make_pair(0, 0);
}
Edge::Edge(float w, int u, int v)
{
    weight = w;
    vertices = make_pair(u, v);
}

Node::Node(float x, float y, float z, float t)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
}

Graph::Graph(GraphType type, int V)
{
    this->vertices = V;
    this->Vchoose2 = V * (V - 1) / 2;
    // Track number of edges cut from total
    long num_cut = 0;

    std::random_device rd;
    std::mt19937_64 randomEngine = std::mt19937_64(rd());
    std::uniform_real_distribution<double> randDist = std::uniform_real_distribution<double>(0, 1);

    if (type == RAND)
    {
        float threshold = 1.1 * 18.4 * pow(V, -0.99);
        clock_t timer = clock();

        for (int i = 0; i < vertices - 1; i++)
        {
            for (int j = i + 1; j < vertices; j++)
            {
                float r = randDist(randomEngine);
                if (r > threshold)
                {
                    num_cut++;
                    continue;
                }
                this->addEdge(r, i, j);
            }
        }

        if (TIMER)
            cout /* << "Rand generation time: "  */ << ((double)(clock() - timer)) / CLOCKS_PER_SEC
                                                    << ", " /*  << endl */;
    }
    else if (type == UNIT_SQ)
    {
        float threshold = 1.1 * 3.19 * pow(V, -0.495);
        vector<Node> nodes;
        clock_t timer = clock();

        // Generate random nodes
        for (int i = 0; i < vertices - 1; i++)
        {
            double x = randDist(randomEngine);
            double y = randDist(randomEngine);
            nodes.push_back(Node(x, y));
        }

        // Store edges as Euclidean distances
        for (int i = 0; i < vertices - 1; i++)
        {
            for (int j = i + 1; j < vertices; j++)
            {
                Node n1 = nodes[i];
                Node n2 = nodes[j];
                // Calculate distance between each pair of nodes and store edges
                float distance = sqrt(pow((n1.x - n2.x), 2.0) + pow((n1.y - n2.y), 2.0));
                if (distance > threshold)
                {
                    num_cut++;
                    continue;
                }
                this->addEdge(distance, i, j);
            }
        }
        if (TIMER)
            cout /* << "2D generation time: " */ << ((double)(clock() - timer)) / CLOCKS_PER_SEC
                                                 << ", " /* << endl */;
    }
    else if (type == UNIT_CUBE)
    {
        float threshold = 1.3 * 1.43 * pow(V, -0.29);
        vector<Node> nodes;
        clock_t timer = clock();

        // Generate random nodes
        for (int i = 0; i < vertices - 1; i++)
        {
            double x = randDist(randomEngine);
            double y = randDist(randomEngine);
            double z = randDist(randomEngine);
            nodes.push_back(Node(x, y, z));
        }

        // Store edges as Euclidean distances
        for (int i = 0; i < vertices - 1; i++)
        {
            for (int j = i + 1; j < vertices; j++)
            {
                Node n1 = nodes[i];
                Node n2 = nodes[j];
                // Calculate distance between each pair of nodes and store edges
                float distance = sqrt(pow((n1.x - n2.x), 2.0) + pow((n1.y - n2.y), 2.0) + pow((n1.z - n2.z), 2.0));
                if (distance > threshold)
                {
                    num_cut++;
                    continue;
                }
                this->addEdge(distance, i, j);
            }
        }
        if (TIMER)
            cout /* << "3D generation time: " */ << ((double)(clock() - timer)) / CLOCKS_PER_SEC
                                                 << ", " /* endl */;
    }
    else if (type == HYPERCUBE)
    {
        float threshold = 1.1 * 1.49 * pow(V, -0.223);
        vector<Node> nodes;
        clock_t timer = clock();

        // Generate random nodes
        for (int i = 0; i < vertices - 1; i++)
        {
            double x = randDist(randomEngine);
            double y = randDist(randomEngine);
            double z = randDist(randomEngine);
            double t = randDist(randomEngine);
            nodes.push_back(Node(x, y, z, t));
        }

        // Store edges as Euclidean distances
        for (int i = 0; i < vertices - 1; i++)
        {
            for (int j = i + 1; j < vertices; j++)
            {
                Node n1 = nodes[i];
                Node n2 = nodes[j];
                // Calculate distance between each pair of nodes and store edges
                float distance = sqrt(pow((n1.x - n2.x), 2.0) + pow((n1.y - n2.y), 2.0) + pow((n1.z - n2.z), 2.0) + pow((n1.t - n2.t), 2.0));
                if (distance > threshold)
                {
                    num_cut++;
                    continue;
                }
                this->addEdge(distance, i, j);
            }
        }
        if (TIMER)
            cout /* << "4D generation time: " */ << ((double)(clock() - timer)) / CLOCKS_PER_SEC
                                                 << ", " /* endl */;
    }
    else
    {
        throw "Invalid graph type";
    }

    clock_t timer = clock();
    this->sortEdges();
    if (TIMER)
        cout /* << "Sorting time: " */ << ((double)(clock() - timer)) / CLOCKS_PER_SEC
                                       << ", " /* endl */;
}

void Graph::addEdge(float weight, int u, int v)
{
    Edge e = Edge(weight, u, v);
    edges.push_back(e);
}

bool compareEdge(const Edge &u, const Edge &v) { return u.weight < v.weight; }

void Graph::sortEdges()
{
    sort(edges.begin(), edges.end(), &compareEdge);
    // Multi-thread system
    // sort(std::execution::par_unseq, edges.begin(), edges.end(), [](const Edge& u, const Edge&v){ return u.weight < v.weight; });
}

void Graph::print_graph()
{
    cout << endl << "GRAPH BELOW" << endl;
    for (int i = 0; i < this->edges.size(); i++)
    {
        Edge edge = this->edges[i];
        std::cout << "[" << edge.weight << ": (" << edge.vertices.first << ", "
                  << edge.vertices.second << ")] " << endl;
    }
    cout << endl;
    cout.flush();
}

float Graph::kruskals()
{

    float total_weight = 0;
    float greatest_weight = 0;
    UnionFind u = UnionFind(this->vertices);

    for (int i = 0; i < this->edges.size(); i++)
    {
        // If the size of UnionFind component includes all the vertices,
        // we have completed the mst
        if (u.getActiveComponentSize() == this->vertices)
            break;

        Edge edge = this->edges[i];
        if (!u.connected(edge.vertices.first, edge.vertices.second))
        {
            u.unify(edge.vertices.first, edge.vertices.second);
            total_weight += edge.weight;
            greatest_weight = edge.weight;
        }
    }

    // Verify that the MST is valid and connected
    for (int i = 0; i < u.getSize() - 1; i++)
        for (int j = i + 1; j < u.getSize(); j++)
            assert(u.connected(i, j) == 1);

    if (G_WEIGHT) cout << "Greatest weight: " <<  greatest_weight << ", ";
    return total_weight;
}
