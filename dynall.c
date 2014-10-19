/* Dynall.c
 *
 * A first round test of dynamically allocating large entries.
 *   Necessary functions:
 *     init(): start the system
 *     add(item)
 *     removeAt(index)
 *     removeAt(item)
 *     finalize(): finish the system
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "dynall.h"

#define MAX_CAPACITY 80000

void print_results();
void privateAdd(int, int);
void add_straight_to_array(int);

int size;
int *storage[MAX_CAPACITY];

int main() {
	clock_t startTime = clock();

	init();

	clock_t initTime = clock();

	if (storage == NULL) {
		printf("ERROR: Failed to allocate memory for data store.\n");
		exit(-1);
	}

	printf("INFO: Ready to go, pointer = %p\n", storage);

	clock_t addStartTime = clock();

	for (int idx = 0; idx < MAX_CAPACITY; idx++) {
        add(idx);
	}

	clock_t addEndTime = clock();

	print_results();

	deleteAt(2);	// Removes the 3.
	deleteAt(4);	// Removes the 4.

	print_results();

	add(6);
	add(7);

	print_results();

	finalize();

	printf("Init time: %f ms\n", ((double) initTime - startTime) / (CLOCKS_PER_SEC / 1000.0));
	printf("Add  time: %f ms\n", ((double) addEndTime - addStartTime) / (CLOCKS_PER_SEC / 1000.0));

	add_straight_to_array(MAX_CAPACITY);

}

void init() {
	size = 0;
}

void add(int value) {
	privateAdd(size, value);
}

void insertAt(int index, int value) {
	if (index < 0 || index >= size) {
		return;
	}

	for (int i = size - 1; i > index; i--) {
		storage[i + 1] = storage[i];
	}

	privateAdd(index, value);
}

// Precondition: index is known valid.
void privateAdd(int index, int value) {
	int *newValuePointer = (int *) malloc(sizeof(int));

	if (newValuePointer == NULL) {
		printf("Error allocating memory.\n");
		finalize();
		exit(-1);
	}

	*newValuePointer = value;
	storage[index] = newValuePointer;

	size++;
}


void deleteAt(int index) {
	if (index < 0 || index >= size) {
		return;
	}

    storage[index] = storage[size - 1];
	storage[size - 1] = NULL;

	--size;
}

void print_results() {
	printf("\n");

	int max = size < 10 ? size : 10;
	printf("size = %d\n", size);

    for (int i = 0; i < max; i++) {
    	printf("Entry %d: %p = %d\n", i, storage[i], *storage[i]);
    }
}

void finalize() {
	for (int i = 0; i < size; ++i) {
		free(storage[i]);
	}
}

void add_straight_to_array(int size) {
	int storagex[MAX_CAPACITY];

	clock_t startTime = clock();

	for (int i = 0; i < size; i++) {
		storagex[i] = i;
	}

	clock_t endTime = clock();

	printf("Addx time: %f ms\n", ((double) endTime - startTime) / (CLOCKS_PER_SEC / 1000.0));
}

