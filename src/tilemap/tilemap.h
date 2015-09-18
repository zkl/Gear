#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <map>
#include <tinyxml2.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tileset.h"
#include "layer.h"
#include "imagelayer.h"
#include "objectlayer.h"
#include "../object.h"
#include "../color.h"
#include "../image.h"

using namespace tinyxml2;

class TileMap : public Object
{
public:
	TileMap();
	~TileMap();
	
	bool load(const char * file);

	void move(int x, int y); // pix
	void scorll(int dx, int dy); // pix
	int  getGid(int x, int y);
	int  getGridGid(int colum, int row);
	bool setGid(int x, int y, int gid);
	int  convertPositionFromCoordinate(int x, int y);
	int  convertPositionFromGrid(int colum, int row);

	int getGid(int position);

	ObjectLayer* getObjectLayer();

	// 宽度和高度(单位像素)
	int  width();
	int  height();
	int  tilewidth();
	int  tileheight();
	int  colum();
	int  row();

	void draw(SDL_Renderer * renderer);
private:
	void analyzeMapInfo(XMLElement * element);
	void analyzeTileset(XMLElement * element);
	void anylyzeLayers(XMLElement * element);
	void anylyzeImageLayer(XMLElement * element);
	void drawlayer(Layer * layer);
	void clear();

	Tileset * findTilesetByGid(int gid);

	int _w, _h;
	int _x, _y;
	int _tileWidth, _tileHeight;
	Color _bgColor;

	// name -> layer
	std::map<std::string, Layer * > _layers;

	// name -> tileset
	std::map<std::string, Tileset*> _tilesets;

	char _basePath[256];
	ObjectLayer _objects;
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
	for(std::map<std::string, Layer*>::iterator it = _layers.begin(); it != _layers.end() && gid == 0; it++)
		gid = it->second->getGid(position);

	return gid;
}

inline int TileMap::getGid(int position)
{
	int gid = 0;
	for(std::map<std::string, Layer*>::iterator it = _layers.begin(); it != _layers.end() && gid == 0; it++)
		gid = it->second->getGid(position);

	return gid;
}

inline int TileMap::width()
{
	return _w*_tileWidth;
}

inline int TileMap::height()
{
	return _h*_tileHeight;
}

inline int TileMap::tilewidth()
{
	return _tileWidth;
}

inline int TileMap::tileheight()
{
	return _tileHeight;
}

inline int TileMap::colum()
{
	return _w;
}
inline int TileMap::row()
{
	return _h;
}

inline int TileMap::convertPositionFromGrid(int colum, int row)
{
	return colum + row * _w;
}

inline int TileMap::convertPositionFromCoordinate(int x, int y)
{
	return x/_tileWidth + (y/_tileHeight)*_w;
}

inline ObjectLayer* TileMap::getObjectLayer()
{
	return &_objects;
}

#endif
