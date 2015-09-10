#include <stdio.h>
#include "objectpool.h"

ObjectPool * ObjectPool::instance()
{
	static ObjectPool pool;
	return &pool;
}

void ObjectPool::push(Ref * r)
{
	m_objects.push_back(r);
}

void ObjectPool::clear()
{

	std::vector<Ref *>::iterator it = m_objects.begin();
	while(it != m_objects.end())
		(*it++)->def();

	m_objects.clear();
}
