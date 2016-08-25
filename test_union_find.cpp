#include <iostream>

#include "union_find.h"

int main(int argc, char const *argv[])
{
	Union_Find uf = build_union_find(5);

	make_union(uf,0,1);
	make_union(uf,1,2);
	make_union(uf,3,4);

	for (int i = 0; i < 5; ++i)
	{
		cout << "Parent[" << i << "] = " << find(uf,i) << " | Rank[" << i << "] = " << uf.rank[i] << endl;
	}

	return 0;
}
