#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <SDL2/SDL.h>
#include "ref.h"

class Object : public Ref
{
public:
	Object();
	virtual ~Object();

	int x();
	int y();
	bool visiable();
	bool actived();
	void setActive(bool active = true);
	void setPosition(int x, int y);
	void setVisiable(bool visiable = true);
	bool appendChild(Object * child);
	Object * parent(){return m_parent;}

	virtual bool init();
	virtual void draw(SDL_Renderer * renderer);
	virtual void update(unsigned int dt);

protected:
	int _x, _y;   // 当前位置
	int _px, _py; // 上一次的位置 

private:
	void removeChild(Object * child);

	bool _visiable;
	bool _actived;
	Object * m_parent;
	std::vector <Object * > m_children;
};

inline int Object::x() 
{
	return _x;
}

inline int Object::y() 
{
	return _y;
}

inline bool Object::actived()
{
	return _actived;
}

inline void Object::setActive(bool active)
{
	_actived = active;
}

inline void Object::setPosition(int x, int y) 
{
	_x = x; 
	_y = y;
}

inline bool Object::visiable()
{
	return _visiable;
}

inline void Object::setVisiable(bool visiable)
{
	_visiable = visiable;	
}


#endif
