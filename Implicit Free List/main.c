#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "stdbool.h"

#include "memory_allocator.h"

void test_implicit_free_list()
{
	void* memoryPool = malloc(100);
	MemoryAllocator* memoryAlloc = MemoryAllocator_init (memoryPool,100);
	int *ptr1 = MemoryAllocator_allocate (memoryAlloc, 5 * sizeof(int));
	int i;
	for (i = 0; i < 5; i++)
	{
		*((int *)ptr1 + i) = i;
	}
	
	for (i = 0; i < 5; i++)
	{
		printf("%d", ptr1[i]);
	}
	printf("\n");
	
	char* ptr2 = MemoryAllocator_allocate (memoryAlloc, 24);
	char* str = "My name is Naama Baran!";
	
	for (i = 0 ;str[i] != '\0'; i++)
	{
		ptr2[i] = str[i];
	}
	ptr2[i] = '\0';
	
	for (i = 0 ;ptr2[i] != '\0'; i++)
	{
		printf("%c", ptr2[i]);
	}
	printf("\n");
	
	char* ptr3 = MemoryAllocator_allocate (memoryAlloc, 30);
	if (!ptr3)
		printf("allocate failed\n");
		
	void *tmp = (size_t*)ptr1 - 1;
	MemoryAllocator_optimize (memoryAlloc);
	MemoryAllocator_free (memoryAlloc, ptr1);
		
	MemoryAllocator_free (memoryAlloc, ptr2);
	printf("matadata: %lu\n", *((size_t*)tmp));
	MemoryAllocator_optimize (memoryAlloc);
	printf("matadata: %lu\n", *((size_t*)tmp));
	
	
	free(MemoryAllocator_release(&memoryAlloc));
}

int main()
{
	test_implicit_free_list();
	
	
	return 0;
}
