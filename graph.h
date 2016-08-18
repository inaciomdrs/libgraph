#include <algorithm>
#include <cmath>
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
typedef list< list<int>* > Connected_Components;
typedef map<Edge,double> weights;

typedef enum {
	white, gray, black
} color;

typedef struct {
	color  *colors;
	int    *parents;
	double *distances;
	int    *start_time;
	int    *finish_time;
} graph_data;

typedef struct {
	int number;
	int weight;
} weighted_int;

#define FALSE 0
#define TRUE  1

#define FIRST_VERTEX 0

#define INIT_TIME 1

#define FIRST_COLOR 0
#define NO_COLOR -1

#define NO_PARENT -1

Graph build_graph(int** matrix, int size);

Graph build_graph(list<Edge> edge_list, int vertex_quantity);

Graph transpose_of(Graph graph, int number_of_vertices);

graph_data initialize_graph_data(int size);

bool compare_weighted_ints(weighted_int a, weighted_int b);

list<int> neighbours(Graph graph, int vertex);

int in_degree(Graph graph, int number_of_vertices, int vertex);

int out_degree(Graph graph, int number_of_vertices, int vertex);

int degree_of(Graph graph, int number_of_vertices, int vertex);

graph_data dfs(Graph graph, int number_of_vertices, int start_vertex);

graph_data dfs_complete(Graph graph, int number_of_vertices);

void dfs_visit(Graph graph, int number_of_vertices, int start_vertex, graph_data & data, int & time);

int* dfs_complete_with_colors(Graph graph, int number_of_vertices, weighted_int* order, int & max_color);

void dfs_visit_with_colors(Graph graph, int number_of_vertices, int start_vertex, int* & colors, int color, bool* & visited);

graph_data bfs(Graph graph, int number_of_vertices, int start_vertex);

bool is_reachable(Graph graph, int number_of_vertices, int vertex_u, int vertex_v);

list<int> path_between(Graph graph, int number_of_vertices, int vertex_u, int vertex_v);

void make_path(int vertex_u, int vertex_v, int *parents, list<int> & path);

bool is_connected(Graph graph, int number_of_vertices);

bool test_connectivity(Graph graph, int number_of_vertices, int vertex);

bool has_cycle(Graph graph, int number_of_vertices);

bool detect_cycles(Graph graph, int number_of_vertices, int vertex_v, bool* & visited);

list<int> topological_sort_degree_strategy(Graph graph, int number_of_vertices);

list<int> topological_sort_dfs_strategy(Graph graph, int number_of_vertices);

void topological_dfs(Graph graph, int number_of_vertices, int vertex, color* & colors, list<int> & total_order);

Connected_Components connected_components_brute_force(Graph graph, int number_of_vertices);

Connected_Components connected_components_kosaraju_sharir(Graph graph, int number_of_vertices);

int** transitive_closure(Graph graph, int number_of_vertices);

int** mutual_reachability_matrix(int **transitive_closure, int size);

int** simple_reachability_matrix(Graph graph, int number_of_vertices);

#endif