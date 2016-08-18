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

Graph build_graph(list<Edge> edge_list, int vertex_quantity){
	Graph graph = new list<int>[vertex_quantity];	

	for (list< Edge >::iterator i = edge_list.begin(); i != edge_list.end(); ++i)
	{
		graph[i->first].push_back(i->second);
	}

	return graph;
}

Graph transpose_of(Graph graph, int number_of_vertices){
	Graph t_graph = new list<int>[number_of_vertices];

	list<int> v_neighbours;

	for (int i = 0; i < number_of_vertices; ++i)
	{
		v_neighbours = neighbours(graph,i);

		for (list<int>::iterator u = v_neighbours.begin(); u != v_neighbours.end(); ++u)
		{
			t_graph[*u].push_back(i);
		}
	}

	return t_graph;
}

graph_data initialize_graph_data(int size){
	graph_data data;
	
	data.colors      = new color[size];
	data.parents     = new int[size];
	data.distances   = new double[size];
	data.start_time  = new int[size];
	data.finish_time = new int[size];

	return data;
}

list<int> neighbours(Graph graph, int vertex){
	return graph[vertex];
}

int in_degree(Graph graph, int number_of_vertices, int vertex){
	list<int> vertex_neighbours;

	int degree = 0;
	for(int i = FIRST_VERTEX; i < number_of_vertices; i++){
		if(i == vertex){ continue; }

		vertex_neighbours = neighbours(graph,i);

		if(find(vertex_neighbours.begin(),vertex_neighbours.end(),vertex) != vertex_neighbours.end()){
			degree++;
		}
	}

	return degree;
}

int out_degree(Graph graph, int number_of_vertices, int vertex){
	return neighbours(graph,vertex).size();
}

int degree_of(Graph graph, int number_of_vertices, int vertex){
	return out_degree(graph,number_of_vertices,vertex);
}

graph_data dfs(Graph graph, int number_of_vertices, int start_vertex){
	graph_data traverse_data = initialize_graph_data(number_of_vertices);

	for (int i = 0; i < number_of_vertices; ++i)
	{
		traverse_data.colors[i] = white;
		traverse_data.parents[i] = NO_PARENT;
		traverse_data.distances[i] = 0;
	}

	int time = INIT_TIME;
	
	dfs_visit(graph,number_of_vertices,start_vertex,traverse_data,time);

	return traverse_data;
}

graph_data dfs_complete(Graph graph, int number_of_vertices){
	graph_data traverse_data = initialize_graph_data(number_of_vertices);

	for (int i = 0; i < number_of_vertices; ++i)
	{
		traverse_data.colors[i] = white;
		traverse_data.parents[i] = NO_PARENT;
		traverse_data.distances[i] = 0;
	}

	int time = INIT_TIME;

	for (int i = 0; i < number_of_vertices; ++i)
	{
		if(traverse_data.colors[i] == white)
		{
			dfs_visit(graph,number_of_vertices,i,traverse_data,time);
		}
	}

	return traverse_data;
}

void dfs_visit(Graph graph, int number_of_vertices, int start_vertex, graph_data & data, int & time){
	data.colors[start_vertex] = gray;
	data.start_time[start_vertex] = time;
	time++;

	list<int> v_neighbours = neighbours(graph,start_vertex);

	for(list<int>::iterator it = v_neighbours.begin(); it != v_neighbours.end(); it++){
		if(data.colors[*it] == white){
			data.parents[*it] = start_vertex;
			dfs_visit(graph,number_of_vertices,*it,data,time);
		}
	}

	data.colors[start_vertex] = black;
	data.finish_time[start_vertex] = time;
	time++;
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
	list<int> v_neighbours;
	while(!Q.empty())
	{
		vertex = Q.front();
		Q.pop();
		v_neighbours = neighbours(graph,vertex);

		for(list<int>::iterator it = v_neighbours.begin(); it != v_neighbours.end(); it++)
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
	list<int> v_neighbours;
	while(!Q.empty())
	{
		vertex = Q.front();
		Q.pop();
		v_neighbours = neighbours(graph,vertex);

		for(list<int>::iterator it = v_neighbours.begin(); it != v_neighbours.end(); it++)
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
	for (int i = 0; i < number_of_vertices; ++i)
	{
		if(!test_connectivity(graph,number_of_vertices,i)){
			return false;
		}
	}

	return true;
}

bool test_connectivity(Graph graph, int number_of_vertices, int vertex){
	graph_data g_data = dfs(graph,number_of_vertices,vertex);
	color *colors = g_data.colors;
	for (int i = 0; i < number_of_vertices; ++i)
	{
		if(colors[i] == white){
			return false;
		}
	}
	return true;
}

bool has_cycle(Graph graph, int number_of_vertices){
	bool *visited = new bool[number_of_vertices];

	for (int i = 0; i < number_of_vertices; ++i)
	{
		visited[i] = false;
	}

	bool has_it_cycle;

	for (int i = 0; i < number_of_vertices; ++i)
	{
		if(!visited[i]){
			has_it_cycle = detect_cycles(graph,number_of_vertices,i,visited);
			if(has_it_cycle){
				return true;
			}
		}
	}

	return false;

}

bool detect_cycles(Graph graph, int number_of_vertices, int vertex_v, bool* & visited){
	color *colors = new color[number_of_vertices];
	int *parents = new int[number_of_vertices];

	for (int i = 0; i < number_of_vertices; ++i)
	{
		colors[i] = white;
		parents[i] = NO_PARENT;
	}

	queue<int> Q;
	Q.push(vertex_v);

	int vertex = vertex_v;
	list<int> v_neighbours;
	while(!Q.empty())
	{
		vertex = Q.front();
		Q.pop();
		v_neighbours = neighbours(graph,vertex);

		for(list<int>::iterator it = v_neighbours.begin(); it != v_neighbours.end(); it++)
		{
			if(colors[*it] == gray)
			{
				return true;
			}

			else if(colors[*it] == white)
			{
				Q.push(*it);
				colors[*it] = gray;
				parents[*it] = vertex;
				visited[*it] = true;
			}
		}

		colors[vertex] = black;	
	}
	return false;
}

list<int> topological_sort_degree_strategy(Graph graph, int number_of_vertices){
	int *degrees = new int[number_of_vertices];
	bool *included = new bool[number_of_vertices];

	list<int> total_order;

	queue<int> Q;

	for (int i = 0; i < number_of_vertices; ++i)
	{
		degrees[i] = in_degree(graph,number_of_vertices,i);
		if(degrees[i] == 0){
			total_order.push_back(i);
			Q.push(i);
			included[i] = true;
		} else {
			included[i] = false;
		}
	}	

	int vertex;
	list<int> vertex_neighbours;
	while(!Q.empty()){
		vertex = Q.front();
		Q.pop();

		vertex_neighbours = neighbours(graph,vertex);

		for(list<int>::iterator it = vertex_neighbours.begin(); it != vertex_neighbours.end(); it++)
		{
			if((--degrees[*it] == 0) && (included[*it] == false)){
				total_order.push_back(*it);
				Q.push(*it);
				included[*it] = true;
			}
		}		
	}

	return total_order;
}

list<int> topological_sort_dfs_strategy(Graph graph, int number_of_vertices){
	list<int> total_order;
	color *colors = new color[number_of_vertices];

	for (int i = 0; i < number_of_vertices; ++i)
	{
		colors[i] = white;
	}

	colors[FIRST_VERTEX] = gray;

	topological_dfs(graph,number_of_vertices,FIRST_VERTEX,colors,total_order);

	return total_order;
}

void topological_dfs(Graph graph, int number_of_vertices, int vertex, color* & colors, list<int> & total_order){
	list<int> vertex_neighbours = neighbours(graph,vertex);

	for (list<int>::iterator vi = vertex_neighbours.begin(); vi != vertex_neighbours.end(); ++vi)
	{
		if(colors[*vi] == white){
			colors[*vi] = gray;
			topological_dfs(graph,number_of_vertices,*vi,colors,total_order);
		}
	}

	colors[vertex] = black;
	total_order.push_front(vertex);
}

Connected_Components connected_components_brute_force(Graph graph, int number_of_vertices){
	Connected_Components components;

	int** t_closure = transitive_closure(graph,number_of_vertices);
	int** mutual_reach_matrix = mutual_reachability_matrix(t_closure,number_of_vertices);

	bool* visited = new bool[number_of_vertices];
	fill(visited,visited+number_of_vertices,false);

	components.push_back(new list<int>);

	for (int i = 0; i < number_of_vertices; ++i)
	{
		if(visited[i]){
			continue;
		}

		components.push_back(new list<int>);
		components.back()->push_back(i);
		for (int j = i + 1; j < number_of_vertices; ++j)
		{
			if(mutual_reach_matrix[i][j] == TRUE){
				components.back()->push_back(j);
				visited[j] = true;
			}
		}

		visited[i] = true;
	}
	
	return components;
}

int** transitive_closure(Graph graph, int number_of_vertices){
	int** reachability_matrix = simple_reachability_matrix(graph,number_of_vertices);

	for (int i = 0; i < number_of_vertices; ++i)
	{
		reachability_matrix[i][i] = TRUE;
	}

	for (double n = 0; n < log2(number_of_vertices); ++n)
	{
		for (int i = 0; i < number_of_vertices; ++i)
		{
			for (int j = 0; j < number_of_vertices; ++j)
			{
				if(reachability_matrix[i][j] == TRUE)
				{
					for (int k = 0; k < number_of_vertices; ++k)
					{	
						if(reachability_matrix[j][k] == TRUE)
						{
							reachability_matrix[i][k] = TRUE;
						}
					}
				}
			}
		}
	}	

	return reachability_matrix;	
}

int** mutual_reachability_matrix(int **transitive_closure, int size){
	int **matrix = new int*[size];

	for (int i = 0; i < size; ++i)
	{
		matrix[i] = new int[size];
		for (int j = 0; j < size; ++j)
		{
			if((transitive_closure[i][j] == TRUE) && (transitive_closure[j][i] == TRUE)){
				matrix[i][j] = TRUE;
			} else {
				matrix[i][j] = FALSE;
			}
		}
	}

	return matrix;
}

int** simple_reachability_matrix(Graph graph, int number_of_vertices){
	int **matrix = new int*[number_of_vertices];

	list<int> vertex_neighbours;
	
	for(int i = 0; i < number_of_vertices; i++)
	{
		matrix[i] = new int[number_of_vertices];
		
		vertex_neighbours = neighbours(graph,i);
		
		for (int j = 0; j < number_of_vertices; ++j)
		{
			if(find(vertex_neighbours.begin(),vertex_neighbours.end(),j) != vertex_neighbours.end()){
				matrix[i][j] = TRUE;
			} else {
				matrix[i][j] = FALSE;
			}
		}

		matrix[i][i] = TRUE;
	}

	return matrix;
}	