#include <stdio.h>
#include <stdlib.h> // malloc and free

int main() {
	int size = 5;

	// malloc asks the os for (5*4 bytes) of space on HEAP
	// it returns the pointer (the address) to the start of that block
	int *my_array = malloc(size * sizeof(int));

	// safety check: always make sure the OS actually gave you the memory
	if (my_array == NULL) {
		printf("Memory allocation failed!\n");
		return 1;
	}

	// use the pointer
	// just like an array to fill with data
	for (int i = 0; i < size; i++) {
		my_array[i] = (i + 1) * 10;
	}

	// (void*) to dereference?
	printf("array at address %p contains:\n", (void*)my_array);
	for (int i = 0; i < size; i++) {
		printf("element %d: %d\n", i, my_array[i]);
	}

	// manual cleanup
	free(my_array);

	return 0;
}