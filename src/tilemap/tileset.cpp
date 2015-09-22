#include "tileset.h"

Tileset::Tileset(const std::string name, unsigned long fgid,
	int tileWidth, int tileHeight, const char* file) :
	_firsGid(fgid),
	_tileWidth(tileWidth),
	_tileHeight(tileHeight)
{
	if(_image.load(file))
		_lastGid = _image.width()/_tileWidth * _image.height()/_tileHeight + _firsGid;
}

Tileset::~Tileset()
{
}

void Tileset::copy(SDL_Surface * surface, int x, int y, unsigned long gid) 
{
	if(_image.empty())
		return ;

	int w = _image.width()/_tileWidth;

	_image.drawEx(surface, x, y, _tileWidth, _tileHeight,((gid-_firsGid)%w)*_tileWidth,
		((gid-_firsGid)/w)*_tileHeight, _tileWidth, _tileHeight);
}
