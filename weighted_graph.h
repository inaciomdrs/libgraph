#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <list>
#include <map>
#include <queue>
#include <utility>

#include "heap.h"

using namespace std;

#ifndef __WEIGHTED_GRAPH_H__
#define __WEIGHTED_GRAPH_H__

typedef struct {
	int value;
	double weight;
} w_int;

typedef struct {
	int u, v;
	double weight;
} w_edge;

typedef list<w_edge>::iterator w_edge_iterator;
typedef list<w_int>::iterator  w_int_iterator;

typedef list<w_int>* w_graph;
typedef list<int> path;

#define NO_WEIGHT 0
#define NO_PARENT -1

bool compare_w_int(w_int a, w_int b);

void print_w_graph(w_graph G, int vertex_quantity);

bool bellman_ford(list<w_edge> edges, int vertex_quantity, int source, int* & parents, double* & distances);

void dijkstra(w_graph G, int vertex_quantity, w_int source, int* & parents, double* & distances);

void floyd_warshall(double** & matrix, int N);

#endif