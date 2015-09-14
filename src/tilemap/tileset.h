#ifndef TILE_SET_H
#define TILE_SET_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../image.h"

class Tileset
{
public:
	Tileset(const std::string name, unsigned long fgid,
		int tileWidth, int tileHeight, const char* file);
	~Tileset();

	inline int fgid();
	void copy(SDL_Surface* surface, int x, int y, unsigned long gid);

private:
	int _firsGid;
	int _tileWidth, _tileHeight;

	Image _image;
};

inline int Tileset::fgid()
{
	return _firsGid;
}

#endif
