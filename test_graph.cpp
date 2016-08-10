#include <iostream>
#include "graph.h"

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

	cout << "Running dfs..." << endl;
	int FIRST_VERTEX = 0;

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

	// Clean data
	for(int i = 0; i < size; i++)
	{
		delete matrix[i];
	}

	delete matrix;
	delete graph;

	return 0;
}