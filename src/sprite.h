#ifndef SPRITE_H
#define SPRITE_H

#ifdef LINUX
#include <sys/time.h>
#endif

#include <SDL2/SDL.h>
#include "object.h"

class Sprite : public Object
{
public:
	~Sprite(){}

	static Sprite * create(int stx, int sty, int w, int h, int row, int column,
		const char * file);

	virtual bool init();
	virtual void draw(SDL_Renderer * renderer);
	virtual void update(unsigned int dt);

	inline void setPosition(int x, int y){
		m_x = x; m_y = y;}
	void setInterval(unsigned int interval);

	inline int x(){
		return m_x;}
	
	inline int y(){
		return m_y;}

private:

	int m_step;
	int m_x, m_y, m_stx, m_sty, m_w, m_h, m_row, m_column;
	unsigned int m_interval;
	unsigned int m_uptime;
	SDL_Texture * m_texture;
	SDL_Surface * m_surface;
};

#endif
