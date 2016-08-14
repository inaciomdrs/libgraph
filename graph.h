#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <list>
#include <map>
#include <queue>
#include <utility>

using namespace std;

#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef list<int>* Graph;
typedef pair<int,int> Edge;
typedef map<Edge,double> Edge_Weight;

typedef enum {
	white, gray, black
} color;

typedef struct {
	color  *colors;
	int    *parents;
	double *distances;
} graph_data;

#define FALSE 0
#define TRUE  1

#define FIRST_VERTEX 0

#define NO_PARENT -1

Graph build_graph(int** matrix, int size);

graph_data initialize_graph_data(int size);

list<int> neighbours(Graph graph, int vertex);

int in_degree(Graph graph, int number_of_vertices, int vertex);

int out_degree(Graph graph, int number_of_vertices, int vertex);

int degree_of(Graph graph, int number_of_vertices, int vertex);

graph_data dfs(Graph graph, int number_of_vertices, int start_vertex);

void dfs_visit(Graph graph, int number_of_vertices, int start_vertex, graph_data & data);

graph_data bfs(Graph graph, int number_of_vertices, int start_vertex);

bool is_reachable(Graph graph, int number_of_vertices, int vertex_u, int vertex_v);

list<int> path_between(Graph graph, int number_of_vertices, int vertex_u, int vertex_v);

void make_path(int vertex_u, int vertex_v, int *parents, list<int> & path);

bool is_connected(Graph graph, int number_of_vertices);

bool has_cycle(Graph graph, int number_of_vertices);

bool detect_cycles(Graph graph, int number_of_vertices, int vertex_v, bool* & visited);

list<int> topological_sort(Graph graph, int number_of_vertices);

#endif