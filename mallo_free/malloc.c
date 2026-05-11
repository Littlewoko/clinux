#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

// linked list for each contiguous block
// points to next block
struct block_meta {
	size_t size;
	struct block_meta *next;
	int free;
};

#define META_SIZE sizeof(struct block_meta)
void *global_base = NULL;

// finding free available block
struct block_meta *find_free_block(struct block_meta **last, size_t size) {
	struct block_meta *current = global_base;

	while (current && !(current -> free && current -> size >= size)) {
		*last = current;
		current = current->next;
	}

	return current;
}

// requesting space from os
struct block_meta *request_space(struct block_meta *last, size_t size) {
	struct block_meta *block;
	// point block at end of break area
	block = sbrk(0);
	// expand break area to cover block size
	void *request = sbrk(size + META_SIZE);

	assert(request != (void*) -1); //sbrk failed

	if (last) {
		last->next = block;
	}

	block->size = size;
	block->next = NULL;
	block->free = 0;
	return block;
}

void *malloc_test(size_t size) {
	struct block_meta *block;

	if (size <= 0) {
		return NULL;
	}

	if (!global_base) {
		block = request_space(NULL, size);
		if (!block) return NULL;
		global_base = block;
	} else {
		struct block_meta *last = global_base;
		// moves 'last' during find_free_block so when passed 
		// to request_space it is at the end of the linked list
		block = find_free_block(&last, size);
		if (!block) {
			block = request_space(last, size);
			if (!block) return NULL;
		} else {
			block->free = 0; // no longer free
		}
	}

	return (block + 1);
}

void free_test(void *ptr) {
	if (!ptr) return;

	struct block_meta *block_ptr = (struct block_meta*)ptr - 1;
	block_ptr->free = 1;
}

int main() {
	printf("--- Starting ----\n");

	// allocate space for int
	int *num = (int*)malloc_test(sizeof(int));
	if (num == NULL) {
		printf("failed int");
		return 1;
	}

	*num = 42;
	printf("Allocated integer at %p with value: %d\n", (void*)num, *num);

	//allocate space for string
	char *str = (char*)malloc_test(100 * sizeof(char));
	if (str == NULL) {
		printf("failed str");
		return 1;
	}

	strcpy(str, "Hello, world!");
	printf("allocated string at %p: %s\n", (void*)str, str);

	// free the memory
	printf("%s\n", "freeing...");
	free_test(num);
	free_test(str);

	// reallocate;
	char *new_str = (char*)malloc_test(50 * sizeof(char));
	printf("reallocated 50 bytes at %p: ", (void*)new_str);

	return 0;
}