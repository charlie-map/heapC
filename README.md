# heap
###### Charlie Hall

This is an implementation of a fibonacci heap, which is usually used for search problems such as Dijkstra's. This will utilize a simple `payload` and `weight` for each input, and everything else can be summed up within the following functions:

1. [Heap Creation - `heap_create()`](#create-the-heap)
2. [Heap Insertion - `heap_push()`](#push-to-the-heap)
3. [Heap Peek - `heap_peek()`](#peek-at-the-heap)
4. [Heap Pop - `heap_pop()`](#pop-off-the-heap)
5. [Heap Decrease Key - `heap_decrease_key()`](#decrease-key-heap)
6. [Heap Destruction - `heap_destroy()`](#destroy-the-heap)

# create the heap
To create a heap, there will be a few parameters needed. First, to include the `heap.h` library, use the following header file:

```C
#include "heap.h"
```

At that point, the creation of a heap just uses the `heap_create()` function, which has a single input: a comparable. The comparable function should return an `int` (either `0` (false) or `1` (true)) which represents if a certain value should become the min (or max) of the heap. The comparable will take in two `void *`'s. An example that uses `int *` for a min heap could be:

```C
int compare(void *weight1, void *weight2) {
    return *(int *) weight1 < *(int *)weight2;
}
```

This can then be used as the input for creating the heap pointer:

```C
heap_t *heap = heap_create(compare);
```

Since the user has to create the comparable, the process of changing this heap from a min heap to a max heap (for integer weights) would be as easy changing the `<` to a `>` in the `compare()` function.

# push to the heap
The inputs for this function will take the heap pointer, a payload pointer, and the pointer to the weight of that payload. Both the payload and the weight are `void *` pointers, meaning this heap is easily utilizable in many different general situations. The `heap_push()` function also returns a `void *` pointer to the heap node, which can be used in [decreasing the key](#decrease-key-heap) of that node. The following example uses a `char *` as the payload and an `int *` as the weight (assuming the same heap as the one created in the [Heap creation](#create-the-heap) section is used):

```C
char *word1 = malloc(sizeof(char) * 11);
strcpy(word1, "some value");

int *weight1 = malloc(sizeof(int));
*weight1 = 50;
void *heap_node1 = heap_push(head, word1, weight1);
```

# peek at the heap
Peeking at the heap is the process of looking at the minimum (or maximum depending on the comparable function used). The function does not remove said value from the heap (see [Heap pop](##pop-off-the-heap)). This function returns a `void *` pointer to the payload of the min(max)imum value.
The following example utilizes the previous created heap to peek at the min(max)imum value currently in the heap.

```C
void *peek = heap_peek(heap);

printf("A peek at the heap returns: %s", (char *) peek);
```

Expected output:
```
A peek at the heap returns: some value
```

# pop off the heap
Similar to [heap peeking](#peek-at-the-heap), but instead removes the entire value from the heap and returns it, which means the next use of the `heap_peek()` function will result in a different value.
This example pushes a smaller value into the heap and then deletes said value (assuming a minimum heap).

```C
char *word2 = malloc(sizeof(char) * 16);
strcpy(word2, "different value");

int *weight2 = malloc(sizeof(int));
*weight2 = 4;
void *heap_node2 = heap_push(head, word2, weight2);

printf("Current minimum: %s\n", heap_peek(head));

char *returnPayload = (char *) heap_pop(head);

printf("Removed minimum: %s\n", returnPayload);

printf("New minimum: %s\n", heap_peek(head));
```

Expected output:
```
Current minimum: different value (AKA the payload matched with the weight: 4)
Removed minimum: different value
New minimum: some value (AKA the payload matched with the weight: 50)
```

# decrease key heap
Decrease key takes a `void *` pointer to a node in the heap and a pointer to a new weight. This goes into the heap and finds that node and decreases the weight, which will involve checking the current min/max for adjustments as well. The following example is based off the example in [heap popping](#pop-off-the-heap) which will insert a new value and then change the weight.

```C
char *word3 = malloc(sizeof(char) * 13);
strcpy(word3, "decrease key");

int *weight3 = malloc(sizeof(int));
*weight3 = 500;
void *heap_node3 = heap_push(head, word3, weight3);

printf("Current minimum: %s\n", (char *) heap_peek(head));

int *newWeight3 = malloc(sizeof(int));
*newWeight3 = 2;
heap_decrease_key(head, heap_node3, newWeight3);

printf("New minimum: %s\n", (char *) heap_peek(head));
```

Expected output:
```
Current minimum: some value (AKA payload associated with the weight 50)
New minimum: decrease key (AKA payload that transferred from weight 500 to weight 2)
```

This assumes that the key is strictly decreasing for a min heap and strictly increasing for a max heap since this will not check children of a heap node.

# destroy the heap
Heap destruction takes the pointer to the heap head and will DFS through the heap to delete all heap pointers. The function returns nothing.

```C
heap_destroy(&head);
```

***Note:*** This will not `free()` and payloads or weights, so there is an assumption that those are freed by the user.
