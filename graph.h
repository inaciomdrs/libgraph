#include <list>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef list<int>* Graph;

typedef struct {
	int *colors;
	int *parents;
	int *distances;
} graph_data;

#define FALSE 0
#define TRUE  1

Graph build_graph(int** matrix, int size);

graph_data dfs(Graph graph, int number_of_vertices);

graph_data bfs(Graph graph, int number_of_vertices);

#endif