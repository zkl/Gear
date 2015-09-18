#ifdef LINUX
#include <unistd.h>
#endif

#include <stdlib.h>
#include <time.h>
#include "objectpool.h"
#include "runner.h"
#include "sprite.h"
#include "tilemap/tilemap.h"

bool Runner::init(const char * title, int w, int h, int flags)
{
	m_isRunning = true;
	m_luptime = 0;
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG);

	m_window = SDL_CreateWindow(title, 100, 100, w, h, flags);
	if(m_window == 0)
		return false;

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	if(m_renderer == 0)
		return false;

	m_world = new World();

	//Sprite * sprite0 = Sprite::create(0, 0, 115, 117, 6, 1, "image/a1.png");
	//Sprite * sprite1 = Sprite::create(0, 0, 192, 192, 10, 5, "image/66RPG_sc_03.png");
	//Sprite * map = Sprite::create(0, 0, 960, 540, 1, 1, "image/bg.jpg");
	//
	
	_image = new Image("image/a1.png");

	_tilemap = new TileMap();
	_tilemap->load("map1.tmx");
	m_world->appendChild(_tilemap);

	_sprite = new SpriteSheet();
	_sprite->addFrames("om.png", 0, 0, 163, 133, 2, 6);
	_sprite->setPosition(102, 42);
	_sprite->setPlaySpeed(20);
	m_world->appendChild(_sprite);

	_sprite = new SpriteSheet();
	_sprite->addFrames("promoimages.png", 0, 0, 65, 65, 8, 8);
	_sprite->setPosition(302, 42);
	_sprite->setPlaySpeed(10);
	_sprite->play();

	m_world->appendChild(_sprite);

	srand((unsigned int)time(0));
	return true;
}

void Runner::update()
{
	unsigned int time = SDL_GetTicks();
	m_world->update(time - m_luptime);
	m_luptime = time;

	std::vector<Sprite *>::iterator it = m_sprites.begin();
	while(it != m_sprites.end())
	{
		(*it)->setPosition((*it)->x()-2, (*it)->y());
		if((*it)->x() < -100)
		{
			(*it)->def();
			it = m_sprites.erase(it);
		}
		else
		{
			it++;
		}
	}

	ObjectPool::instance()->clear();
}

void Runner::render()
{
	SDL_RenderClear(m_renderer);
	m_world->draw(m_renderer);
	_image->draw(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Runner::handleEvents()
{
	SDL_Event event;
	if(SDL_WaitEventTimeout(&event, 1) == 0)
		return ;

	switch(event.type)
	{
	case SDL_QUIT:
		{
			m_isRunning = false;
			break;
		}
	case SDL_KEYDOWN:
		{
			Sprite * sprite = Sprite::create(0, 0, 163, 133, 3, 2, "image/om.png");
			//Sprite * sprite = Sprite::create(0, 0, 192, 192, 10, 5, "image/66RPG_sc_03.png");
			sprite->setPosition(1000, rand()%540);
			sprite->setInterval(80);
			m_world->appendChild(sprite);

			m_sprites.push_back(sprite);
			break;
		}
	case SDL_MOUSEMOTION:
		{
			if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
			{
				_tilemap->move(event.motion.xrel, event.motion.yrel);
			}
		}
	default:
		break;
	}
}
