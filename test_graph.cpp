#include <iostream>
#include "graph.h"

void print_graph(Graph graph, int size){
	list<int> neighbours;
	int number_of_neighbours;
	for (int i = 0; i < size; ++i)
	{
		neighbours = graph[i];
		cout << i << ": ";
		for (list<int>::iterator it = neighbours.begin(); it != neighbours.end(); ++it)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
}

void run_dfs(Graph graph, int size){
	cout << "Running dfs..." << endl;

	graph_data dfs_data = dfs(graph,size,FIRST_VERTEX);

	cout << "Colors: ";
	for (int i = 0; i < size; ++i)
	{
		cout << dfs_data.colors[i] << " ";
	}
	cout << endl;

	cout << "Parents: ";
	for (int i = 0; i < size; ++i)
	{
		cout << "parent[" << i << "]: " << dfs_data.parents[i] << endl;
	}
}

void run_bfs(Graph graph, int size){
	cout << "Running bfs..." << endl;

	graph_data bfs_data = bfs(graph,size,FIRST_VERTEX);

	cout << "Colors: ";
	for (int i = 0; i < size; ++i)
	{
		cout << bfs_data.colors[i] << " ";
	}
	cout << endl;

	cout << "Parents: ";
	for (int i = 0; i < size; ++i)
	{
		cout << "parent[" << i << "]: " << bfs_data.parents[i] << endl;
	}

	cout << "Distances: ";
	for (int i = 0; i < size; ++i)
	{
		cout << "distances[" << i << "," << " 0]: " << bfs_data.distances[i] << endl;
	}
}

void check_reachability(Graph graph, int size){
	int vertex_u, vertex_v;

	cout << "Checking out reachability..." << endl;
	cin  >> vertex_u >> vertex_v;

	bool are_reachable = is_reachable(graph,size,vertex_u,vertex_v);

	cout << vertex_u << " and " << vertex_v << " are ";
	
	if(!are_reachable){
		cout << "not ";
	}

	cout << "reachable each other" << endl;
}

void print_path(list<int> path){
	for (list<int>::iterator i = path.begin(); i != path.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;
}

void check_path(Graph graph, int size){
	int vertex_u, vertex_v;

	cout << "Checking existence of path..." << endl;
	cin  >> vertex_u >> vertex_v;

	list<int> path = path_between(graph,size,vertex_u,vertex_v);

	cout << "There is ";

	if(path.size() == 0){
		cout << "no path between " << vertex_u << " and " << vertex_v << endl;
	} else {
		cout << "a path between " << vertex_u << " and " << vertex_v << endl;
		print_path(path);
	}
}

int main(int argc, char **argv)
{
	int size;
	cin >> size;

	int **matrix = new int*[size];

	for(int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
		for (int j = 0; j < size; ++j)
		{
			cin >> matrix[i][j];
		}
	}

	Graph graph = build_graph(matrix,size);
	
	print_graph(graph,size);

	cout << "Degrees" << endl;

	for (int i = 0; i < size; ++i)
	{
		cout << i << " - IN: " << in_degree(graph,size,i) << " | OUT: " << out_degree(graph,size,i) << endl;
	}

	cout << "Is this graph connected? ";

	if(is_connected(graph,size)){
		cout << "Yes";
	} else {
		cout << "No";
	}

	cout << endl;

	cout << "Is there any cycle in this graph? ";

	if(has_cycle(graph,size)){
		cout << "Yes";
	} else {
		cout << "No";
	}

	cout << endl;

	cout << "Topological ordering for this graph\n";
	list<int> order = topological_sort(graph,size);

	for(list<int>::iterator it = order.begin(); it != order.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	return 0;
}