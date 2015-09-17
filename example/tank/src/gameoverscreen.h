#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include "src/screen.h"
#include "src/director.h"

class GameOverScreen : public Screen
{
public:
	virtual bool init() ;
	virtual void begin();
	virtual void update(unsigned int dt);
	virtual void draw(SDL_Renderer* randerer);
	virtual void handleEvent(const SDL_Event& event);

private:
	int _uptime;
	Image _image;
};


inline bool GameOverScreen::init()
{
	return _image.load("gameover.png");
}

inline void GameOverScreen::begin()
{
	_uptime = 0;
}

inline void GameOverScreen::update(unsigned int dt)
{
	_uptime += dt;
}

inline void GameOverScreen::draw(SDL_Renderer* randerer)
{
	_image.draw(randerer);
}

inline void GameOverScreen::handleEvent(const SDL_Event& event)
{
	if(_uptime < 1000)
		return ;

	if(event.type == SDL_KEYDOWN)
		Director::getDirector()->changeScreen("Menu");
}


#endif