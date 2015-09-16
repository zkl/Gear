#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <map>
#include <tinyxml2.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tileset.h"
#include "layer.h"
#include "imagelayer.h"
#include "../object.h"
#include "../color.h"
#include "../image.h"

using namespace tinyxml2;

class TileMap : public Object
{
public:
	TileMap();
	~TileMap();
	
	// @todo 
	virtual bool blocked(int x, int y, int role);

	bool load(const char * file);
	void move(int x, int y);
	int  getGid(int x, int y);
	int  getGridGid(int colum, int row);
	bool setGid(int x, int y, int gid);

	// 宽度和高度(单位像素)
	int  width();
	int  height();
	int  tilsetWidth();
	int  tilsetHeight();
	int  tilsetColum();
	int  tilsetRow();

	void draw(SDL_Renderer * renderer);
private:
	void analyzeMapInfo(XMLElement * element);
	void analyzeTileset(XMLElement * element);
	void anylyzeLayers(XMLElement * element);
	void anylyzeImageLayer(XMLElement * element);
	void drawlayer(Layer * layer);

	Tileset * getTileset(int gid);

	int _w, _h;
	int _x, _y;
	int _tileWidth, _tileHeight;
	Color _bgColor;

	//std::vector<Tileset *> _tilesets;
	std::vector<Layer * > _layers;

	// name -> tileset
	std::map<std::string, Tileset*> _tilesets;

	Image _image;
};

inline void TileMap::move(int x, int y)
{
	_x += x; 
	_y += y;
}

inline int TileMap::getGid(int x, int y)
{
	int row = y/_tileHeight;
	int colum = x/_tileWidth;
	return this->getGridGid(colum, row);
}

inline int TileMap::getGridGid(int colum, int row)
{
	int gid = 0;
	int position = row * _w + colum;
	for(unsigned int i=0; i<_layers.size() && gid == 0; i++)
		gid = _layers[i]->getGid(position);

	return gid;
}

inline bool TileMap::blocked(int x, int y, int role)
{
	if(getGid(x, y) != 0)
		return true;

	return false;
}

inline int TileMap::width()
{
	return _w*_tileWidth;
}

inline int TileMap::height()
{
	return _h*_tileHeight;
}

inline int TileMap::tilsetWidth()
{
	return _tileWidth;
}

inline int TileMap::tilsetHeight()
{
	return _tileHeight;
}

inline int TileMap::tilsetColum()
{
	return _w;
}
inline int TileMap::tilsetRow()
{
	return _h;
}

#endif
