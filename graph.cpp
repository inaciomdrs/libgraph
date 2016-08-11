#include "graph.h"

Graph build_graph(int** matrix, int size) {
	Graph graph = new list<int>[size];

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if(matrix[i][j] == TRUE){
				graph[i].push_back(j);
			}
		}
	}

	return graph;	
}

graph_data initialize_graph_data(int size){
	graph_data data;
	
	data.colors    = new color[size];
	data.parents   = new int[size];
	data.distances = new double[size];

	return data;
}

graph_data dfs(Graph graph, int number_of_vertices, int start_vertex){
	graph_data traverse_data = initialize_graph_data(number_of_vertices);

	for (int i = 0; i < number_of_vertices; ++i)
	{
		traverse_data.colors[i] = white;
		traverse_data.parents[i] = NO_PARENT;
		traverse_data.distances[i] = 0;
	}

	dfs_visit(graph,number_of_vertices,start_vertex,traverse_data);

	return traverse_data;
}

void dfs_visit(Graph graph, int number_of_vertices, int start_vertex, graph_data & data){
	data.colors[start_vertex] = gray;

	list<int> neighbours = graph[start_vertex];

	for(list<int>::iterator it = neighbours.begin(); it != neighbours.end(); it++){
		if(data.colors[*it] == white){
			data.parents[*it] = start_vertex;
			dfs_visit(graph,number_of_vertices,*it,data);
		}
	}

	data.colors[start_vertex] = black;
}

graph_data bfs(Graph graph, int number_of_vertices, int start_vertex){
	graph_data traverse_data = initialize_graph_data(number_of_vertices);

	for (int i = 0; i < number_of_vertices; ++i)
	{
		traverse_data.colors[i] = white;
		traverse_data.parents[i] = NO_PARENT;
		traverse_data.distances[i] = 0;
	}

	queue<int> Q;

	traverse_data.colors[start_vertex] = gray;

	Q.push(start_vertex);

	int vertex;
	list<int> neighbours;
	while(!Q.empty())
	{
		vertex = Q.front();
		Q.pop();
		neighbours = graph[vertex];

		for(list<int>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
		{
			if(traverse_data.colors[*it] == white)
			{
				Q.push(*it);
				traverse_data.colors[*it] = gray;
				traverse_data.parents[*it] = vertex;
				traverse_data.distances[*it] = traverse_data.distances[vertex] + 1;
			}
		}

		traverse_data.colors[vertex] = black;	
	}

	return traverse_data;
}

bool is_reachable(Graph graph, int number_of_vertices, int vertex_u, int vertex_v){
	color* colors = new color[number_of_vertices];

	queue<int> Q;
	colors[vertex_u] = gray;

	Q.push(vertex_u);

	int vertex;
	list<int> neighbours;
	while(!Q.empty())
	{
		vertex = Q.front();
		Q.pop();
		neighbours = graph[vertex];

		for(list<int>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
		{
			if(*it == vertex_v){
				return true;
			} else if(colors[*it] == white){
				colors[*it] = gray;
				Q.push(*it);
			}
		}
	}
	
	return false;
}

list<int> path_between(Graph graph, int number_of_vertices, int vertex_u, int vertex_v){
	list<int> path;

	graph_data g_data = bfs(graph,number_of_vertices,vertex_u);
	
	int vertex_v_color = g_data.colors[vertex_v];
	
	if(vertex_v_color != white){
		make_path(vertex_u,vertex_v,g_data.parents,path);
	}

	return path;

}

void make_path(int vertex_u, int vertex_v, int *parents, list<int> & path){
	for(int vertex = vertex_v; vertex != vertex_u; vertex = parents[vertex]){
		path.push_front(vertex);
	}
	path.push_front(vertex_u);
}

bool is_connected(Graph graph, int number_of_vertices){
	
	graph_data g_data = dfs(graph,number_of_vertices,FIRST_VERTEX);
	color *colors = g_data.colors;
	for (int i = 0; i < number_of_vertices; ++i)
	{
		if(colors[i] == white){
			return false;
		}
	}
	return true;
}

#include <iostream>
bool has_cycle(Graph graph, int number_of_vertices){
	color *colors = new color[number_of_vertices];
	int *parents = new int[number_of_vertices];

	for (int i = 0; i < number_of_vertices; ++i)
	{
		colors[i] = white;
		parents[i] = NO_PARENT;
	}
	colors[FIRST_VERTEX] = gray;

	int vertex_v = FIRST_VERTEX;

	int has_it_cycle = detect_cycles(graph,number_of_vertices,FIRST_VERTEX,colors,parents);
	
	if(has_it_cycle){
		return true;
	}

	for (int i = 0; i < number_of_vertices; ++i)
	{
		if(colors[i] == white){
			has_it_cycle = detect_cycles(graph,number_of_vertices,i,colors,parents);
			if(has_it_cycle){
				return true;
			}
		}
	}

	return false;

}

bool detect_cycles(Graph graph, int number_of_vertices, int vertex_v, color* & colors, int* & parents){
	queue<int> Q;
	Q.push(vertex_v);

	int vertex = vertex_v;
	list<int> neighbours;
	while(!Q.empty())
	{
		vertex = Q.front();
		Q.pop();
		neighbours = graph[vertex];

		for(list<int>::iterator it = neighbours.begin(); it != neighbours.end(); it++)
		{
			if(*it == parents[vertex])
			{
				continue;
			}
			else if(colors[*it] == white)
			{
				Q.push(*it);
				colors[*it] = gray;
				parents[*it] = vertex;
			}
			else
			{
				return true;
			}
		}

		colors[vertex] = black;	
	}
	return false;
}