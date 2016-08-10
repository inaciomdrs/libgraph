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

graph_data dfs(Graph graph, int number_of_vertices){
	
}

graph_data bfs(Graph graph, int number_of_vertices){
	
}