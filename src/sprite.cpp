#include "SDL2/SDL_image.h"
#include "objectpool.h"
#include "sprite.h"

Sprite * Sprite::create(int stx, int sty, int w, int h, int row, int column,
	const char * file)
{
	Sprite * s = new Sprite();
	s->init();

	s->m_surface = IMG_Load(file);
	s->m_stx = stx;
	s->m_sty = sty;
	s->m_w = w;
	s->m_h = h;
	s->m_row = row;
	s->m_column = column;

	return s;
}

bool Sprite::init()
{
	m_w = 0;
	m_h = 0;
	m_x = 0;
	m_y = 0;

	m_stx = 0;
	m_sty = 0;

	m_row = 0;
	m_column = 0;
	m_interval = 100;

	m_step = 0;
	m_surface = 0;
	m_uptime = 0;
	m_texture = 0;

	return true;
}


void Sprite::setInterval(unsigned int interval)
{
	m_interval = interval;
}

void Sprite::update(unsigned int dt)
{
	m_uptime += dt;
	if(m_uptime > m_interval )
	{
		m_uptime = 0;
		if(++m_step >= m_column*m_row)
			m_step = 0;
	}
}

void Sprite::draw(SDL_Renderer * renderer)
{
	if (NULL == m_texture) 
		m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);  
	
	if (NULL == m_texture) 
		return;

	SDL_Rect dstRect;
	SDL_Rect srcRect;
	
	dstRect.w = m_w;
	dstRect.h = m_h;
	dstRect.x = m_x;
	dstRect.y = m_y;

	srcRect.w = m_w;
	srcRect.h = m_h;
	srcRect.x = m_stx+(m_step%m_column)*m_w;
	srcRect.y = m_sty+(m_step/m_column)*m_h;

	SDL_RenderCopy(renderer, m_texture, &srcRect, &dstRect);  
}
