#ifndef MOVIE_H
#define MOVIE_H

#include "object.h"

class Movie : public  Object
{
public:
	virtual void draw(SDL_Renderer * renderer);
	virtual bool init(){return false;}
	virtual void update(unsigned int dt);

	void play();
	void stop();
	void addFrame();
	bool playing();
private:

};

inline void Movie::draw(SDL_Renderer * renderer)
{
}

inline bool Movie::init()
{
	return true;
}

inline void Movie::update(unsigned int dt)
{
}

#endif