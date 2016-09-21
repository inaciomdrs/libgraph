#include "heap.h"

int front(Min_Heap heap){
	return heap[POSITION_MINIMUM];
}

int0 enqueue(Min_Heap & heap, int element){
	heap.push_back(element);
	return heapify(heap,heap.size()-1);
}

int heapify(Min_Heap & heap, int position){
	int parent_position = PARENT(position);

	int swap_aux;
	if((parent_position >= POSITION_MINIMUM) && (heap[position] < heap[parent_position])){
		swap_aux = heap[position];
		heap[position] = heap[parent_position];
		heap[parent_position] = swap_aux;

		heapify(heap,parent_position);
	} else {
		return position;
	}
}

int dequeue(Min_Heap & heap){
	int f = front(heap);

	heap.erase(heap.begin());

	int position = 0; 
	int v_left, v_right;

	while(position < heap.size()){
		v_left  = heap[LEFT(position)];
		v_right = heap[RIGHT(position)];

		if(v_left < v_right){
			position = LEFT(position);
		} else {
			position = RIGHT(position);
		}

		if(position < heap.size()){
			heapify(heap,position);	
		}
	}


	return f;
}