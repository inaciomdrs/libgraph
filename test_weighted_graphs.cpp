#include "weighted_graph.h"

int main(int argc, char const *argv[])
{
	int N;

	scanf("%d",&N);

	w_graph G = new list<w_int>[N];

	list<w_edge> edges;
	w_edge edge;

	w_int wi;
	while(scanf("%d %d %lf",&edge.u,&edge.v,&edge.weight) != EOF)
	{
		edge.u--;
		edge.v--;

		wi.value = edge.v;
		wi.weight = edge.weight;

		edges.push_back(edge);
		G[edge.u].push_back(wi);
	}

	print_w_graph(G,N);

	int *parents   = new int[N];
	double *distances = new double[N];

	if(bellman_ford(edges, N, 0, parents, distances)){
		for (int i = 0; i < N; ++i)
		{
			//printf("Distance to %d: %.1lf\n",i,distances[i]);
			printf("Parent of %d: %d\n",i,parents[i]);
		}
	}

	printf("==============\n");

	parents   = new int[N];
	distances = new double[N];

	dijkstra(G, N, 0, parents, distances);

	for (int i = 0; i < N; ++i)
	{
		//printf("Distance to %d: %.1lf\n",i,distances[i]);
		printf("Parent of %d: %d\n",i,parents[i]);
	}

	delete parents;
	delete distances;

	return 0;
}