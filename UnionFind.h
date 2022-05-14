#include <vector>

using namespace std;

#ifndef UnionFind
class UnionFind
{
private:
	int size;
	int activeComponent;
	vector<int> sizes;
	vector<int> components;

public:
	UnionFind(int size);

	int find(int node);

	int getActiveComponentSize();

	int componentSize(int node);

	int getSize();

	bool connected(int node1, int node2);

	void unify(int node1, int node2);
};

#endif