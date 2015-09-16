#ifndef BULLET_H
#define BULLET_H

#include "src/object.h"
#include "src/image.h"
#include "src/movie.h"

class Bullet : public Object
{
public:
	Bullet();

	void launch(int direction);
	void explode();
	bool exploding();

	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);

private:
	bool _explorer;
	bool _exploding;
	int _step;
	int _uptime;
	int _direction;

	Movie _bomb;
	Image _image;
};

inline bool Bullet::exploding()
{
	return _exploding;
}

#endif
