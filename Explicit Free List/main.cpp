
#include "person_allocator.h"

void testPersonAllocator()
{
	//-------------------using the new keyword/operator
	PersonAllocator *p1 = (PersonAllocator*)::operator new(sizeof(PersonAllocator));
	*p1 = PersonAllocator("Naama Baran", 211355847, 20);
	std::cout<< "Address of p1: " << p1 << std::endl;
	//std::cout<< "Free List - first block: "<< p1->s_firstfree << std::endl;
	
	//-------------------using the new expression
	PersonAllocator *p2 = new PersonAllocator("Ruth Baran", 211225996, 18);
	std::cout<< "Address of p2: " << p2 <<std::endl;
	//std::cout<< "Free List - first block: "<< p1->s_firstfree << std::endl;
	
	delete p1;
	//std::cout<< "Free List - first block: "<< p2->s_firstfree << std::endl;
	delete p2;
	//std::cout<< "Address of p2: " << p2 <<std::endl;
}

int main()
{
	testPersonAllocator();
	
	return 0;
}
