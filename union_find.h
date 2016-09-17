#include <algorithm>

using namespace std;

#ifndef __UNION_FIND_H__
#define __UNION_FIND_H__

typedef struct {
	int size;
	int *parents;
	int *rank;
} Union_Find;

#define SELF_PARENT -1
#define NO_RANK 0

Union_Find build_union_find(int size);

void make_union(Union_Find union_find, int u_element, int v_element);

int find(Union_Find union_find, int u_element);

#endif
