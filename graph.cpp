#include "graph.h"
#include <iostream>

Graph build_graph(int** matrix, int size) {
	Graph graph = new list<int>[size];

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < i; ++j) {
			if(matrix[i][j] == TRUE){
				graph[i].push_back(j);
				graph[j].push_back(i);
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
	graph_data return_data = initialize_graph_data(number_of_vertices);

	for (int i = 0; i < number_of_vertices; ++i)
	{
		return_data.colors[i] = white;
		return_data.parents[i] = NO_PARENT;
		return_data.distances[i] = 0;
	}

	dfs_visit(graph,number_of_vertices,start_vertex,return_data);

	return return_data;
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
	graph_data return_data = initialize_graph_data(number_of_vertices);

	return return_data;
}