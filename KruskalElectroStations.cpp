#include <iostream>
#include <bits.h>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> iPair;

struct Graph
{
	int V, E;
	vector< pair<int, iPair> > edges;
	vector<int> electro;
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}
	void addElectro(int w) {
		electro.push_back(w);
	}
	void addEdge(int u, int v, int w) {
		edges.push_back({w, {u, v}});
	}
	int KruskalMST();
};
struct DisjointSets
{
	int *parent, *rank;
	int n;
	DisjointSets(int n)
	{
		this->n = n;
		parent = new int[n + 1];
		rank = new int[n + 1];
		for(int i=0; i<=n; i++) {
			rank[i] = 0;
			parent[i] = i;
		}
	}
	int Find(int u)
	{
		if(u != parent[u])
			parent[u] = Find(parent[u]); 
		return parent[u];
	}
	void Union(int x, int y)
	{
		x = Find(x), y = Find(y);
		
		if(rank[x] > rank[y])
			parent[y] = x;
		else
			parent[x] = y;
			
		if(rank[x] == rank[y])
			rank[y]++;
	}
};
int Graph::KruskalMST()
{
	int mst_weight = 0;
	sort(edges.begin(), edges.end());
	DisjointSets ds(V);
	vector<pair<int, iPair>>::iterator it;
	for(it = edges.begin(); it != edges.end(); it++) {
		int u = it->second.first;
		int v = it->second.second;
		int set_u = ds.Find(u);
		int set_v = ds.Find(v);
		if(set_u != set_v && electro[set_u] == 0) {
			cout << "(" << u << ", " << v << ") = " << it->first << endl;
			mst_weight += it->first;
			ds.Union(set_u, set_v);
		}
	}
	return mst_weight;
}
int main() {
	int V = 4, E = 6;
	Graph g(V, E);
	g.addEdge(0, 1, 4);
	g.addEdge(0, 2, 8);
	g.addEdge(0, 3, 9);
	g.addEdge(1, 3, 7);
	g.addEdge(1, 2, 2);
	g.addEdge(2, 3, 1);
	
	g.addElectro(1); g.addElectro(0); g.addElectro(0); g.addElectro(1);
	
    cout << "MST Edges \n"; 
    int mst_wt = g.KruskalMST(); 
	cout << endl;
  	
    cout << "MST Weight = " << mst_wt;
}
