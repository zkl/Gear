#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "object.h"

class World : public Object
{
public:
	virtual bool init();
	
	//b2World * physicsWorld(){return m_physicsWorld;}
private:
	//b2World * m_physicsWorld;
	
};

#endif
