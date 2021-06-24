#include "solver.hpp"

#include <climits>

const int IINF = INT_MAX / 2 - 1;
const double DINF = 32e30;
const double DELTA  = 0.001;

inline int min(int x, int y) {
	return x < y ? x : y;
}

void get_path(Network& graph, ArrayList<int>& path) {
	int n = graph.size();
	int devide = graph.devide();
	
	double* dist = new double[n];
	for (int i = 0; i < n; i++) {
		dist[i] = DINF;
	}
	dist[graph.sorce()] = 0.0;

	int* prev = new int[n];
	for (int i = 0; i < n; i++) {
		prev[i] = -1;
	}

	for (int i = 0; i < n - 1; i++) {
		for (int v = 0; v < devide; v++) {
			for (int u = devide; u < n; u++) {
				if (graph.remaining_capacity(v, u) > 0 && dist[u] > dist[v] + graph.cost(v, u) + DELTA) {
					dist[u] = dist[v] + graph.cost(v, u);
					prev[u] = v;
				}
				
				if (graph.remaining_capacity(u, v) > 0 && dist[v] > dist[u] + graph.cost(u, v) + DELTA) {
					dist[v] = dist[u] + graph.cost(u, v);
					prev[v] = u;
				}
			}
		}
	}

	path.add(graph.sink());

	for (int p = prev[graph.sink()]; p != -1; p = prev[p]) {
		path.add(p);
	}

	delete[] dist;
	delete[] prev;
}

void solve(Network& graph) {
	ArrayList<int> path;

       	get_path(graph, path);
	while (path.length() > 1) {

		int n = path.length();
		int bottleneck = IINF;
		for (int i = 1; i < n; i++) {
			bottleneck = min(bottleneck, graph.remaining_capacity(path.get(i), path.get(i - 1)));
		}

		for (int i = 1; i < n; i++) {
			graph.push(path.get(i), path.get(i - 1), bottleneck);
		}

		path.clear();
		get_path(graph, path);
	}
}
