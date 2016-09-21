#include <cmath>
#include <vector>

using namespace std;

#ifndef __HEAP_H__
#define __HEAP_H__

typedef vector<int> Min_Heap;

#define PARENT(X) (X) >> 1
#define LEFT(X) ((X) << 1) + 1
#define RIGHT(X) LEFT((X)) + 1

#define POSITION_MINIMUM 0

int front(Min_Heap heap);

int enqueue(Min_Heap & heap, int element);

int heapify(Min_Heap & heap, int position);

int dequeue(Min_Heap & heap);

int update_value(Min_Heap & heap, int position, int new_value);

#endif