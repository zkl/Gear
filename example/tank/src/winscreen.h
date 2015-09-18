#ifndef WIN_SCERRN_H 
#define WIN_SCERRN_H 

#include "src/screen.h"
#include "src/director.h"

class WinScreen : public Screen
{
public:
	virtual bool init() ;
	virtual void begin();
	virtual void update(unsigned int dt);
	virtual void draw(SDL_Renderer* randerer);
	virtual void handleEvent(const SDL_Event& event);

private:
	int _uptime;
	Image _message;
	Image _background;
};


inline bool WinScreen::init()
{
	return _background.load("bg.png") && _message.load("win.png");
}

inline void WinScreen::begin()
{
	_uptime = 0;
}

inline void WinScreen::update(unsigned int dt)
{
	_uptime += dt;
}

inline void WinScreen::draw(SDL_Renderer* randerer)
{
	_background.draw(randerer);
	_message.draw(randerer);
}

inline void WinScreen::handleEvent(const SDL_Event& event)
{
	if(_uptime < 2000)
		return ;

	if(event.type == SDL_KEYDOWN)
		Director::getDirector()->changeScreen("Menu");
}

#endif
