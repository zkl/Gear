#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include <vector>
#include <stdio.h>

class ObjectLayer
{
public:
	ObjectLayer();

	void  resize(int size);
	void  setObject(int position, void* obj);
	void* getObject(int position);
	void  clear();

private:
	std::vector<void *> _objects;
};

inline ObjectLayer::ObjectLayer()
{
}

inline void ObjectLayer::resize(int size)
{
	for(int i=0; i<size; i++)
		_objects.push_back(0);
}

inline void ObjectLayer::setObject(int position, void* obj)
{
	_objects[position] = obj;

}

inline void* ObjectLayer::getObject(int position)
{
	if(position < 0)
		printf("ObjectLayer::getObject error -> position < 0\n");

	return _objects[position];
}

inline void ObjectLayer::clear()
{
	for(unsigned int i=0; i<_objects.size(); i++)
		_objects[i] = 0;
}

#endif
