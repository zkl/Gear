#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#include <string>
#include <vector>
#include <SDL2/SDL_image.h>
#include "object.h"

class SpriteSheet : public Object
{
public:
	SpriteSheet();

	/**
	* @brief play 
	*/
	void play();
	void stop();
	void playByStep();
	void setPlaySpeed(int fps);

	/**
	* @brief addFrame 
	*
	* @param resources
	* @param x
	* @param y
	* @param w
	* @param h
	*/
	void addFrame (const char * resources, int x, int y, int w, int h);
	void addFrames(const char * resources, int x, int y, int w, int h,
		int column, int frames);

protected:
	virtual void draw(SDL_Renderer * renderer);
	virtual void update(unsigned int dt);

private:
	SDL_Surface * createSurface(int w, int h);
	
	int  _fps;     // 播放速度
	int  _step;
	int  _luptime;
	int  _w, _h;
	int  _frames;
	bool _update;  // 须要更新Texture
	bool _playing;
	SDL_Surface * _surface;
	SDL_Texture * _texture; // 缓存
};

inline void SpriteSheet::play()
{
	_playing = true;
}

inline void SpriteSheet::stop()
{
	_playing = false;
}

inline void SpriteSheet::playByStep()
{
	++_step >= _frames ? _step = 0 : 0;
}

inline void SpriteSheet::setPlaySpeed(int fps)
{
	_fps = fps;
}

#endif


