#include <cmath>
#include <vector>

using namespace std;

#ifndef __HEAP_H__
#define __HEAP_H__

#define PARENT(X) (X) >> 1
#define LEFT(X) ((X) << 1) + 1
#define RIGHT(X) LEFT((X)) + 1

#define POSITION_MINIMUM 0

template <typename T>
T front(vector<T> heap){
	return heap[POSITION_MINIMUM];
}

template <typename T>
void heapify(vector<T> & heap, int position, bool (*compare)(T,T)){
	int parent_position = PARENT(position);

	T swap_aux;
	if((parent_position >= POSITION_MINIMUM) && (compare(heap[position],heap[parent_position]) == true)){
		swap_aux = heap[position];
		heap[position] = heap[parent_position];
		heap[parent_position] = swap_aux;

		heapify(heap,parent_position,compare);
	}
}

template <typename T>
void enqueue(vector<T> & heap, T element, bool (*compare)(T,T)){
	heap.push_back(element);
	heapify(heap,heap.size()-1,compare);
}

template <typename T>
T dequeue(vector<T> & heap, bool (*compare)(T,T)){
	T f = front(heap);

	heap.erase(heap.begin());

	int position = 0; 
	T v_left, v_right;

	while(position < heap.size()){
		v_left  = heap[LEFT(position)];
		v_right = heap[RIGHT(position)];

		if(compare(v_left,v_right) == true){
			position = LEFT(position);
		} else {
			position = RIGHT(position);
		}

		if(position < heap.size()){
			heapify(heap,position,compare);	
		}
	}

	return f;
}

#endif