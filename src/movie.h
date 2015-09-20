#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include "image.h"
#include "object.h"

class Movie : public  Object
{
public:
	Movie();

	void play();
	void stop();
	bool playing();
	void loop(bool loop = true);
	void setFps(int fps);
	void addFrame(Image* frame);
	void addFrames(Image* image, int x, int y, int w, int h,
		int column, int frames);

	virtual void draw(SDL_Renderer * renderer);
	virtual void update(unsigned int dt);
private:
	bool _loop;
	bool _playing;
	int  _frame;
	unsigned int _uptime;
	unsigned int _interval;
	std::vector<Image *> _frames;
};


inline Movie::Movie() : 
	_loop(false),
	_playing(false),
	_frame(0),
	_uptime(0),
	_interval(1000/60)
{
}

inline void Movie::play()
{
	_playing = true;
	_uptime  = 0;

	this->setActive();
	this->setVisiable();
}

inline void Movie::stop()
{
	this->setActive(false);
	_playing = false;
}

inline bool Movie::playing()
{
	return _playing;
}

inline void Movie::loop(bool loop)
{
	_loop = loop;
}

inline void Movie::setFps(int fps)
{
	_interval = 1000 / fps;
}

inline void Movie::addFrame(Image* frame)
{
	frame->ref();
	_frames.push_back(frame);
}

#endif
