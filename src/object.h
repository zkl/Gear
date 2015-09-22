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

	virtual bool visiable();
	virtual bool actived();
	virtual void setActive(bool active = true);
	virtual void setPosition(int x, int y);
	virtual void setVisiable(bool visiable = true);

	virtual void setId(int id);
	virtual int  id();
	virtual void setType(int type);
	virtual int  type();

	bool appendChild(Object * child);
	Object * parent(){return _parent;}

	virtual void draw(SDL_Renderer * renderer);
	virtual void update(unsigned int dt);

protected:
	int _x, _y;   // 当前位置
	int _px, _py; // 上一次的位置 

private:
	void removeChild(Object * child);

	int  _id;
	int  _type;
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


inline void Object::setId(int id)
{
	_id = id;
}

inline int Object::id()
{
	return _id;
}

inline void Object::setType(int type)
{
	_type = type;
}

inline int Object::type()
{
	return _type;
}

#endif
