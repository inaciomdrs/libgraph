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

	// Clean data
	for(int i = 0; i < size; i++)
	{
		delete matrix[i];
	}

	delete matrix;
	delete graph;

	return 0;
}