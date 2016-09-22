#include <iostream>

#include "heap.h"

bool compare(int a, int b){
	return a < b;
}

int main(int argc, char const *argv[])
{
	vector<int> heap;

	for (int i = 9; i > 0; --i)
	{
		enqueue(heap,i,&compare);
	}

	for (int i = 9; i > 0; --i)
	{
		cout << dequeue(heap,&compare) << " ";
	}

	cout << endl;
	return 0;
}
