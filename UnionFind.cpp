#include "UnionFind.h"
#include <iostream>
#include <vector>

using namespace std;

// class uf::UnionFind {
// private:
//   int size;
//   vector<int> sizes;
//   vector<int> components;

// public:
UnionFind::UnionFind(int size)
{
	if (size < 1)
	{
		cout << "Error: size must be > 0" << endl;
		exit(1);
	}
	this->size = size;
	sizes.reserve(size);
	components.reserve(size);
	activeComponent = 0;

	for (int i = 0; i < size; i++)
	{
		sizes[i] = 1;
		components[i] = i;
	}
}

int UnionFind::find(int node)
{
	int root = node;
	// Find the root of the given node
	while (root != components[root])
		root = components[root];

	// Amortize the path compression
	while (node != root)
	{
		int parent = components[node];
		components[node] = root;
		node = parent;
	}
	return root;
}

int UnionFind::getActiveComponentSize()
{
	return sizes[find(activeComponent)];
}

int UnionFind::componentSize(int node)
{
	return sizes[find(node)];
}

int UnionFind::getSize()
{
	return size;
}

bool UnionFind::connected(int node1, int node2)
{
	return find(node1) == find(node2);
}

void UnionFind::unify(int node1, int node2)
{
	if (connected(node1, node2))
		return;

	int root1 = find(node1);
	int root2 = find(node2);

	// Pick the larger component as the new root
	if (sizes[root1] < sizes[root2])
	{
		activeComponent = root2;	  // update activeComponent int
		sizes[root2] += sizes[root1]; // update size
		sizes[root1] = 0;			  // mark as unused
		components[root1] = root2;	  // link root
	}
	else
	{
		activeComponent = root1;	  // update activeComponent int
		sizes[root1] += sizes[root2]; // update size
		sizes[root2] = 0;			  // mark as unused
		components[root2] = root1;	  // link root
	}
}
