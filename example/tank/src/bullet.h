#ifndef BULLET_H
#define BULLET_H

#include "src/object.h"
#include "src/image.h"

class Bullet : public Object
{
public:
	Bullet();
	void emit(int direction);

	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);
private:
	int _direction;
	int _interval;
	int _uptime;
	Image _image;
};

#endif
