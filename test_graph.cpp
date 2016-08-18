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

	graph_data dfs_data = dfs_complete(graph,size);

	cout << "Colors: ";
	for (int i = 0; i < size; ++i)
	{
		cout << dfs_data.colors[i] << " ";
	}
	cout << endl;

	cout << "Parents:\n";
	for (int i = 0; i < size; ++i)
	{
		cout << "parent[" << i << "]: " << dfs_data.parents[i] << endl;
	}

	cout << "Finish Times:\n";
	for (int i = 0; i < size; ++i)
	{
		cout << "F_Time[" << i << "]: " << dfs_data.finish_time[i] << endl;
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

	cout << "Parents:\n";
	for (int i = 0; i < size; ++i)
	{
		cout << "parent[" << i << "]: " << bfs_data.parents[i] << endl;
	}

	cout << "Distances:\n";
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

	list<Edge> edges;

	int vertex_u;
	int vertex_v;

	int edges_quantity = 0;

	while(cin >> vertex_u >> vertex_v)
	{
		edges.push_back(make_pair(--vertex_u,--vertex_v));
	}

	Graph graph = build_graph(edges,size);
	Graph graph_transposed = transpose_of(graph,size);

	//int **matrix = new int*[size];

	/*for(int i = 0; i < size; i++)
	{
		matrix[i] = new int[size];
		for (int j = 0; j < size; ++j)
		{
			cin >> matrix[i][j];
		}
	}*/

	// Graph graph = build_graph(matrix,size);
	
	print_graph(graph,size);
	cout << "\n==================\n";
	print_graph(graph_transposed,size);
	cout << "\n";

	run_dfs(graph,size);

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

	cout << "Topological ordering (degree strategy) for this graph\n";
	list<int> order = topological_sort_degree_strategy(graph,size);
	for(list<int>::iterator it = order.begin(); it != order.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	cout << "Topological ordering (dfs strategy) for this graph\n";
	order = topological_sort_dfs_strategy(graph,size);
	for(list<int>::iterator it = order.begin(); it != order.end(); it++){
		cout << *it << " ";
	}
	cout << endl;

	cout << "Reachability Matrix" << endl;
	int **matrix = simple_reachability_matrix(graph,size);
	for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}

	cout << "Transitive Closure" << endl;
	matrix = transitive_closure(graph,size);
	for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}	

	cout << "Mutual Reachability Matrix" << endl;
	matrix = mutual_reachability_matrix(matrix,size);
	for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}

	cout << "Connected Components (BRUTE FORCE)" << endl;
	Connected_Components components = connected_components_brute_force(graph,size);

	list<int>* elements;
	for (Connected_Components::iterator i = components.begin(); i != components.end(); ++i)
	{
		elements = *i;
		for (list<int>::iterator elem = elements->begin(); elem != elements->end(); ++elem)
		{
			cout << *elem << " ";
		}
		cout << endl;
	}

	cout << "Connected Components (KOSARAJU AND SHARIR)" << endl;
	components = connected_components_kosaraju_sharir(graph,size);
	
	for (Connected_Components::iterator i = components.begin(); i != components.end(); ++i)
	{
		elements = *i;
		for (list<int>::iterator elem = elements->begin(); elem != elements->end(); ++elem)
		{
			cout << *elem << " ";
		}
		cout << endl;
	}

	return 0;
}