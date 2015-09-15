#ifndef BULLET_H
#define BULLET_H

#include "src/object.h"
#include "src/image.h"
#include "src/movie.h"
#include "tank.h"

class Bullet : public Object
{
public:
	Bullet();
	void emit(int direction);
	void bob();
	void setOwner(Tank* tank);

	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);
private:
	bool _bobing;
	int _direction;
	int _interval;
	int _uptime;
	Tank* _tank;
	Movie _bob;
	Image _image;
};

#endif
