#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <map>
#include "object.h"

class SpriteSheet;

class Animation : public Object
{
public:
	Animation() : _playing(0) {}

	/**
	* @brief play 播放动画
	*
	* @param animation 动画名称
	*/
	void play(const char * animation);

	SpriteSheet * createSpriteSheet(const char * name);

protected:
	void draw(SDL_Renderer * renderer);
	void update(unsigned int dt);
	
private:
	std::string _name;
	SpriteSheet * _playing;
	std::map<std::string, SpriteSheet *> _animations;
};

#endif
