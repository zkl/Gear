#ifndef MOVIE_H
#define MOVIE_H

#include <vector>
#include "image.h"
#include "object.h"

class Movie : public  Object
{
public:
	void play();
	void stop();
	bool playing();
	void loop(bool loop = true);
	void speed(int interval);
	void addFrame(Image* frame);
	void addFrames(Image* image, int x, int y, int w, int h,
		int column, int frames);

	Movie();
	virtual void draw(SDL_Renderer * renderer);
	virtual bool init();
	virtual void update(unsigned int dt);
private:
	bool _loop;
	bool _playing;
	int  _frame;
	int _uptime;
	int _fps;
	std::vector<Image *> _frames;
};


inline Movie::Movie() : 
	_loop(false),
	_playing(false),
	_frame(0),
	_uptime(0),
	_fps(20)
{
}
inline void Movie::play()
{
	_playing = true;
}

inline void Movie::stop()
{
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

inline void Movie::draw(SDL_Renderer* renderer)
{
	if(_frame < _frames.size() && this->visiable())
		_frames[_frame]->draw(renderer, _x, _y);
}

inline bool Movie::init()
{
	return true;
}

inline void Movie::addFrame(Image* frame)
{
	frame->ref();
	_frames.push_back(frame);
}

inline void Movie::update(unsigned int dt)
{
	if(!_playing)
		return ;

	_uptime += dt;
	if(_uptime >= 1000/_fps)
	{
		_uptime = 0;
		if(++_frame >= _frames.size())
		{
			_frame = 0;
			if(!_loop)
				_playing = false;
		}
	}
}

#endif
