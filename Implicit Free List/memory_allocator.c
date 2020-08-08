
#include "malloc.h"
#include "stdbool.h"
#include "assert.h"

#include "memory_allocator.h"

const static int ALIGN = 8;
const static int MDS = sizeof(size_t);

typedef struct MemoryAllocator
{
	void* memoryPool;
	size_t size;
}MemoryAllocator;

//==========================================AUXILIARY FUNCTIONS==========================================

static size_t align (size_t size)
{
	return ((size + MDS)%ALIGN == 0) ? MDS + size : MDS + size + (ALIGN - (size + MDS)%ALIGN);
}

static size_t get_size (void* ptr)
{
	return (*((size_t*)ptr)>>1)<<1 ;
}

static void* the_next_block (void* ptr)
{
	return (char*)ptr + get_size(ptr);
}

static size_t merge_two_free_blocks(void* block)
{
	*((size_t*)block) += get_size((the_next_block (block)));
	printf("merged: %lu",*((size_t*)block));
	return get_size(block);
}

static bool is_allocated(void* block)
{
	return *((size_t*)block)&1;
}

static void split_block(void* block, size_t size)
{
	 *((size_t*)((char*)block + size)) = *((size_t*)block) - size;
	 *((size_t*)block) = size;
}
static void change_sign(size_t *mataData)
{
	*mataData = (*mataData) ^ 1;
}
//===================================END OF AUXILIARY FUNCTIONS======================================

MemoryAllocator* MemoryAllocator_init (void *memoryPool, size_t size)
{
	MemoryAllocator* heap = malloc(sizeof(MemoryAllocator));
	heap->memoryPool = memoryPool;
	size -= ALIGN - (size)%ALIGN;
	*((size_t*)(heap->memoryPool)) = size;
	heap->size = size;
	
	return heap;
}

void * MemoryAllocator_release (MemoryAllocator** allocator)
{
	void* ptr = (*allocator)->memoryPool;
	free(*allocator);
	allocator = NULL;
	return ptr;
}

void * MemoryAllocator_allocate (MemoryAllocator* allocator, size_t size)
{
	void* ptr = allocator->memoryPool;
	size_t sizeRemain = allocator->size;
	size_t curSize;
	size = align(size);
	
	while (sizeRemain >= size)
	{
		curSize = get_size(ptr);
		if (is_allocated(ptr))
		{
			sizeRemain -= get_size(ptr);
			ptr = the_next_block(ptr);
		}
		else
		{
			if (size > curSize)
			{
				if (!is_allocated(the_next_block(ptr)))
				{
					curSize = merge_two_free_blocks(ptr);
				}
				else
				{
					ptr = the_next_block(ptr);
				}
			}
			if (size < curSize)
			{
				split_block(ptr, size);
				curSize = get_size(ptr);
			}
			if (size == curSize)
			{
				change_sign((size_t*)(ptr));
				return (size_t*)(ptr) + 1;
			}
		}
	}
	return NULL;
}

void MemoryAllocator_free (MemoryAllocator* allocator, void *ptr)
{
	assert(ptr);
	change_sign((size_t*)ptr - 1);

	if (!is_allocated(the_next_block((size_t*)ptr-1)))
	{
		merge_two_free_blocks((size_t*)ptr-1);
	}
}

size_t MemoryAllocator_optimize (MemoryAllocator* allocator)
{
	void* ptr =  allocator->memoryPool;
	size_t sizeRemain =  allocator->size;
	void *nextFreeBlock;
	size_t maxSize = 0;
	
	while (sizeRemain > get_size(ptr))
	{
		if (!is_allocated(ptr))
		{
			nextFreeBlock = ptr;
			while (sizeRemain > get_size(ptr) && !is_allocated(the_next_block(nextFreeBlock)))
			{
				nextFreeBlock = the_next_block(nextFreeBlock);
				merge_two_free_blocks(ptr);
			}
			maxSize = (get_size(ptr) > maxSize) ? get_size(ptr) : maxSize;
		}
		sizeRemain -= get_size(ptr);
		ptr = the_next_block(ptr);	
	}
	return maxSize;
}

