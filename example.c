#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

/*
	COMPARE function: returns true or false based on payload value
	the two inputs are payload nodes. If the compare is based on a simple
	integer weight, then the response to this function could be:

		return *(int *) firstWeight < *(int *) secondWeight;

	which would give us the correct response to this function. This
	would result in a MIN heap instead of a MAX based on the "<" symbol
*/
int compare(void *firstWeight, void *secondWeight) {
	return *(int *) firstWeight < *(int *) secondWeight;
}

int main() {
	heap_t *head = heap_create(compare);

	// some unstructured example tests:
	// random payload
	char *word1 = malloc(sizeof(char) * 10);
	strcpy(word1, "first key");
	// random weight
	int *weight1 = malloc(sizeof(int));
	*weight1 = 50;
	void *heap_node1 = heap_push(head, word1, weight1);

	// random payload
	char *word2 = malloc(sizeof(char) * 11);
	strcpy(word2, "second key");
	// random weight
	int *weight2 = malloc(sizeof(int));
	*weight2 = 500;
	void *heap_node2 = heap_push(head, word2, weight2);

	// third random payload
	char *word3 = malloc(sizeof(char) * 10);
	strcpy(word3, "third key");
	// random weight
	int *weight3 = malloc(sizeof(int));
	*weight3 = 4;
	void *heap_node3 = heap_push(head, word3, weight3);


	// test peeking and popping (which should be "third key")
	printf("First peek: %s\n", (char *) heap_peek(head));
	printf("First pop: %s\n\n", (char *) heap_pop(head));

	printf("Second peek: %s\n", (char *) heap_peek(head));

	// use decrease key for changing the weight of second key
	// this change to the second key will result in heap_peek to change
	int *newWeight2 = malloc(sizeof(int));
	*newWeight2 = 2;
	heap_decrease_key(head, heap_node2, newWeight2);
	printf("Second peek after decrease key: %s\n", (char *) heap_peek(head));
	printf("Second pop: %s\n\n", (char *) heap_pop(head));

	// free data
	heap_destroy(&head); // pass pointer to heap

	free(word1);
	free(weight1);
	free(word2);
	free(weight2);
	free(newWeight2);
	free(word3);
	free(weight3);

	return 0;
}