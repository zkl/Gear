#include <algorithm>
#include "object.h"

Object::Object() : 
	m_parent(0),
	_visiable(true),
	_x(0),
	_y(0)
{
}

Object::~Object()
{
	std::vector<Object *>::iterator it = m_children.begin();
	while(it != m_children.end())
		(*it++)->m_parent = 0;

	if(m_parent)
		m_parent->removeChild(this);
}

void Object::removeChild(Object * child)
{
	std::vector<Object *>::iterator it = std::find(
		m_children.begin(), m_children.end(), child);

	if(it != m_children.end())
		m_children.erase(it);
}

bool Object::appendChild(Object * child)
{
	child->m_parent = this;
	m_children.push_back(child);
	return false;
}

void Object::draw(SDL_Renderer * renderer)
{
	if(_visiable)
	{
		std::vector<Object *>::iterator it = m_children.begin();
		while(it != m_children.end())
		{
			if((*it)->visiable())
				(*it)->draw(renderer);

			it++;
		}
	}
}

void Object::update(unsigned int dt)
{
	std::vector<Object *>::iterator it = m_children.begin();
	while(it != m_children.end())
		(*it++)->update(dt);
}
