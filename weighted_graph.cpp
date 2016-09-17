#include "weighted_graph.h"

void print_w_graph(w_graph G, int vertex_quantity){
	for (int v = 0; v < vertex_quantity; ++v)
	{
		printf("%d: ",v);
		for (w_int_iterator w_it = G[v].begin(); w_it != G[v].end(); ++w_it)
		{
			printf("(%d ~ %f) ",w_it->value,w_it->weight);
		}	
		printf("\n");
	}
}

bool bellman_ford(list<w_edge> edges, int vertex_quantity, int source, int* & parents, double* & distances){
	for (int i = 0; i < vertex_quantity; ++i)
	{
		parents[i] = NO_PARENT;
		distances[i] = INT_MAX;
	}

	distances[source] = 0;

	for (int i = 0; i < (vertex_quantity-1); ++i)
	{
		for (w_edge_iterator edge = edges.begin(); edge != edges.end(); ++edge)
		{
			if(distances[edge->v] > (distances[edge->u] + edge->weight)){
				distances[edge->v] = (distances[edge->u] + edge->weight);
				parents[edge->v] = edge->u;
			}
		}
	}

	for (w_edge_iterator edge = edges.begin(); edge != edges.end(); ++edge)
	{
		if(distances[edge->v] > (distances[edge->u] + edge->weight)){
			return false;
		}
	}

	return true;
}