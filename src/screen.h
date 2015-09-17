#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

class Screen
{
public:
	virtual ~Screen();

	virtual bool init() ;
	virtual void begin();
	virtual void end();
	virtual void update(unsigned int dt);
	virtual void draw(SDL_Renderer* randerer);
	virtual void handleEvent(const SDL_Event& event);
};

inline Screen::~Screen(){}
inline bool Screen::init()
{
	return true;
}

inline void Screen::begin(){}
inline void Screen::end(){}
inline void Screen::update(unsigned int dt){}
inline void Screen::draw(SDL_Renderer * randerer){}
inline void Screen::handleEvent(const SDL_Event& event){}

#endif