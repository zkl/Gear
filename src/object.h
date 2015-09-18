#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <SDL2/SDL.h>
#include "ref.h"

#define ADD_CREATE_FUNCTION create()
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
	Object * parent(){return _parent;}

	virtual void draw(SDL_Renderer * renderer);
	virtual void update(unsigned int dt);

protected:
	int _x, _y;   // 当前位置
	int _px, _py; // 上一次的位置 

private:
	void removeChild(Object * child);

	bool _visiable;
	bool _actived;
	Object * _parent;
	std::vector <Object * > _children;
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
