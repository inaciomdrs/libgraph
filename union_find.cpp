#include "union_find.h"

Union_Find build_union_find(int size){
	Union_Find uf;
	uf.size = size;
	uf.parents = new int[size];
	uf.rank = new int[size];

	fill(uf.parents,uf.parents+size,SELF_PARENT);
	fill(uf.rank,uf.rank+size,NO_RANK);

	return uf;
}

void make_union(Union_Find union_find, int u_element, int v_element){
	int u_parent = find(union_find,u_element);
	int v_parent = find(union_find,v_element);

	int u_parent_rank = union_find.rank[u_parent];
	int v_parent_rank = union_find.rank[v_parent];

	if(u_parent_rank > v_parent_rank){
		union_find.parents[v_parent] = u_parent;
	} else {
		union_find.parents[u_parent] = v_parent;
		if(u_parent_rank == v_parent_rank){
			union_find.rank[v_parent]++;
		}
	}

}

int find(Union_Find union_find, int u_element){
	int u_parent = union_find.parents[u_element];

	if(u_parent == SELF_PARENT){
		return u_element;
	} else {
		union_find.parents[u_element] = find(union_find,u_parent);
	}

	return union_find.parents[u_element];
}