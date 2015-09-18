#include <algorithm>
#include "object.h"

Object::Object() : 
	_parent(0),
	_visiable(true),
	_actived(true),
	_x(0),
	_y(0)
{
}

Object::~Object()
{
	std::vector<Object *>::iterator it = _children.begin();
	while(it != _children.end())
		(*it++)->_parent = 0;

	if(_parent)
		_parent->removeChild(this);
}

void Object::removeChild(Object * child)
{
	std::vector<Object *>::iterator it = std::find(_children.begin(), _children.end(), child);

	if(it != _children.end())
		_children.erase(it);
}

bool Object::appendChild(Object * child)
{
	child->_parent = this;
	_children.push_back(child);
	return false;
}

void Object::draw(SDL_Renderer * renderer)
{
	if(_visiable)
	{
		std::vector<Object *>::iterator it = _children.begin();
		while(it != _children.end())
		{
			if((*it)->visiable())
				(*it)->draw(renderer);

			it++;
		}
	}
}

void Object::update(unsigned int dt)
{
	if(_actived)
	{
		std::vector<Object *>::iterator it = _children.begin();
		while(it != _children.end())
		{
			if((*it)->_actived)
				(*it)->update(dt);

			it++;
		}
	}
}
