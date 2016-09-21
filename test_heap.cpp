#include <iostream>

#include "heap.h"

int main(int argc, char const *argv[])
{
	Min_Heap heap;

	for (int i = 9; i > 0; --i)
	{
		enqueue(heap,i);
	}

	for (int i = 9; i > 0; --i)
	{
		cout << dequeue(heap) << " ";
	}

	cout << endl;
	return 0;
}
