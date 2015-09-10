#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include "image.h"
#include "object.h"

class Movie : public  Object
{
public:
	virtual void draw(SDL_Renderer * renderer);
	virtual bool init(){return false;}
	virtual void update(unsigned int dt);

	void play();
	void stop();
	void addFrame(Image* frame);
	bool playing();
	void loop(bool loop = true);
	void speed(int interval);

private:
	bool _loop;
	bool _playing;
	int  _frame;
	std::vector<Image *> _frames;
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