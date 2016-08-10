#include "graph.h"

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