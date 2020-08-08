#ifndef __PERSON_H__
#define __PERSON_H__

#include <cstring> //strcpy
#include <cstddef> //size_t
#include <exception>
#include <iostream>


class Person
{
public:
	Person(const char* name, unsigned int id, unsigned char age);

private:
	unsigned char 	m_age;
	unsigned int 	m_id;
	char 			m_fullname[32];
};



inline Person::Person(const char* name, unsigned int id, unsigned char age)
:m_fullname(),
m_age(age),
m_id(id)
{
	strcpy(m_fullname,name);
}




#endif //__PERSON_H__
