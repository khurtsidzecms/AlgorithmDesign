#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <set>
using namespace std;

class Graph {
	int V;
	int count;
	int preCounter;
	list<int> *adj;
	stack<int> scc;
	stack<int> path;
	bool *ccc;
	int *preOrder;
	vector< set<int> > Components;
public:
	Graph(int V);
	void addEdge(int v, int w);
	void DFSViz(int v);
	void DFS();
};
Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
	ccc = new bool[V];
	preOrder = new int[V];
}
void Graph::addEdge(int v, int w) {
	adj[v].push_back(w);
}
void Graph::DFSViz(int v) {
	preOrder[v] = preCounter;
	preCounter++;
	scc.push(v);
	path.push(v);
	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); i++) {
		if(preOrder[*i] == 0) {
			DFSViz(*i);
		} else if(!ccc[*i]) {
			while(preOrder[*i] < preOrder[path.top()]) {
				path.pop();
			}
		}
	}
	if(path.top() == v) {
		int m;
    		set<int> tmp;
		if(!ccc[v]) {
      			tmp.insert(v);
      			ccc[v] = true;
   		}
		while(v != scc.top()){
			m = scc.top();
		 	if(!ccc[m]) {
				tmp.insert(m);
				ccc[m] = true;
			}
			scc.pop();
		}
		Components.push_back(tmp);
		path.pop();
	}
}
void Graph::DFS() {
	bool *visited = new bool[V];
	
	for(int i=0; i < V; i++) {
		visited[i] = false;
		ccc[i] = false;
		preOrder[i] = 0;
	}
	
	count = 0;
	preCounter = 0;
	for(int i = 0; i < V; i++) {
		if(preOrder[i] == 0) {
			DFSViz(i);
			cout << endl;
		}
	}
	
	cout << "Dzlierad Bmuli Komponentebia:" << endl;
	
	set<int>::iterator j;
	for(int i = 0; i < Components.size(); i++) {
		if(Components[i].begin() != Components[i].end()) {
			for(j = Components[i].begin(); j!=Components[i].end(); j++) {
				cout << *j << " ";
			}
			cout << endl;
			count++;
		}
	}
	
	cout << endl;
	
	cout << "Dzlierad Bmuli Komponentebis Raodenoba: " << count << endl;
}

int main() {
	Graph g(12);
	g.addEdge(0, 1); g.addEdge(1, 2); g.addEdge(1, 4); g.addEdge(1, 3);
	g.addEdge(3, 5); g.addEdge(4, 1); g.addEdge(4, 5); g.addEdge(4, 6);
	g.addEdge(5, 3); g.addEdge(5, 7); g.addEdge(6, 7); g.addEdge(6, 9);
	g.addEdge(7, 10); g.addEdge(8, 6); g.addEdge(9, 8); g.addEdge(10, 11);
	g.addEdge(11, 9);

	cout << "DFS Algorithm" << endl;
	cout << "-------------" << endl;
	g.DFS();

	return 0;
}
