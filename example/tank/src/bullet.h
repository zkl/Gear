#ifndef BULLET_H
#define BULLET_H

#include "src/object.h"
#include "src/image.h"
#include "src/movie.h"

class Bullet : public Object
{
public:
	Bullet();

	void emit(int direction);
	void bob();
	bool bobing();

	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);

private:
	bool _bobing;
	int _interval;
	int _uptime;
	int _direction;

	Movie _bob;
	Image _image;
};

inline bool Bullet::bobing()
{
	return _bobing;
}

#endif
