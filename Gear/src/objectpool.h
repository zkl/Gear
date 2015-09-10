#ifndef OBJECT_POOL
#define OBJECT_POOL

#include <vector>
#include "ref.h"

class ObjectPool
{
public:
	static ObjectPool * instance();

	void push(Ref * r);
	void clear();

private:
	std::vector<Ref *> m_objects;
};

#endif