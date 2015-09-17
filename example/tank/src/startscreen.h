#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "src/screen.h"
#include "src/image.h"

class StartScreen : public Screen
{
public:
	virtual bool init() ;
	virtual void begin();
	virtual void update(unsigned int dt);
	virtual void draw(SDL_Renderer* randerer);
	virtual void handleEvent(const SDL_Event& event);

private:
	int _height;
	int _uptime;
	Image _image;
	Image _message;
};



#endif
