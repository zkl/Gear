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

	inline int minGid();
	inline int maxGid();
	void copy(SDL_Surface* surface, int x, int y, unsigned long gid);

private:
	int _firsGid;
	int _lastGid;
	int _tileWidth, _tileHeight;

	Image _image;
};

inline int Tileset::minGid()
{
	return _firsGid;
}

inline int Tileset::maxGid()
{
	return _lastGid;
}

#endif
