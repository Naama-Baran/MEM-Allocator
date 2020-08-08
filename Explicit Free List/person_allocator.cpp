
#include <exception>
#include "person_allocator.h"


//==================AUXILIARY FUNCTIONS===================

static void initFreeList(Person* memory_pool)
{
	size_t i = 0;
	for (; i < PersonAllocator::NUM_OF_PERSON_IN_MEMORY; i++)
	{
		*(Person**)(memory_pool + i) = memory_pool + i + 1;
	}
	
	*(Person**)(memory_pool+i-1) = NULL;
}

static Person* initMemoryAlloc()
{
	Person* memory_pool = (Person*)::operator new(PersonAllocator::NUM_OF_PERSON_IN_MEMORY*sizeof(Person));
	initFreeList(memory_pool);
	
	return memory_pool;
}

static void throwEmptyFreeList(Person* s_firstFree)
{
	if (!s_firstFree)
	{
		throw std::bad_alloc();
	}
	
}
//==================END AUXILIARY FUNCTIONS===================


//==================INITIALIZING STATIC MEMBERS=====================

Person* PersonAllocator::s_pool = initMemoryAlloc();	
Person* PersonAllocator::s_firstfree = s_pool;

//==================================================================


void* PersonAllocator::operator new(size_t size)
{
	std::cout<< "--------new--------"<< std::endl;
	
	throwEmptyFreeList(s_firstfree);
	
	Person* ptr = s_firstfree;
	s_firstfree = *(Person**)s_firstfree;
	
	return ptr;
}


