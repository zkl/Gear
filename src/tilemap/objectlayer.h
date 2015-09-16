#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include <vector>

class ObjectLayer
{
public:
	ObjectLayer();

	void  resize(int size);
	void  setObject(int position, void* obj);
	void* getObject(int position);

private:
	std::vector<void* > _objects;
};

inline ObjectLayer::ObjectLayer()
{
}

inline void ObjectLayer::resize(int size)
{
	_objects.reserve(size);
	for(int i=0; i<size; i++)
		_objects.push_back(0);
}

inline void ObjectLayer::setObject(int position, void* obj)
{
	_objects[position] = obj;
}

inline void* ObjectLayer::getObject(int position)
{
	return _objects[position];
}


#endif