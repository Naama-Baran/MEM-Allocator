#ifndef __PERSON_ALLOCATOR_H__
#define __PERSON_ALLOCATOR_H__

#include "person.h"

class PersonAllocator 
{
public:
	PersonAllocator(const char* name, unsigned int id, unsigned char age):m_person(name, id, age){};
	
	void* operator new(size_t size);
	void operator delete(void* ptr);

	static const size_t 	NUM_OF_PERSON_IN_MEMORY = 5;
	
private:
	void* operator new[](size_t);
	void operator delete[](void*);
	
	static Person* 	s_pool;
	static Person* 	s_firstfree;
	Person 		m_person;
};

inline void PersonAllocator::operator delete(void* ptr)
{
	std::cout<< "-------delete-------"<< std::endl;
	
	*(Person**)ptr = s_firstfree;
	s_firstfree = (Person*)ptr;
}

#endif 
