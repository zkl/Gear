#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <tinyxml2.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tileset.h"
#include "layer.h"
#include "imagelayer.h"
#include "../object.h"
#include "../color.h"
#include "../image.h"

class TileMap : public Object
{
public:
	TileMap();
	~TileMap();

	bool load(const char * file);
	void move(int x, int y);

	int getGid(int row, int colum);

	// 宽度和高度(单位像素)
	int width();
	int height();
	int tilsetWidth();
	int tilsetHeight();
	int tilsetColum();
	int tilsetRow();

	virtual void draw(SDL_Renderer * renderer);

private:
	void initSurface(tinyxml2::XMLElement * root);
	void loadTileset(tinyxml2::XMLElement * e);
	void loadLayers(tinyxml2::XMLElement * e);
	void loadImageLayer(tinyxml2::XMLElement * e);
	void drawlayer(Layer * layer);

	Tileset * getTileset(int gid);

	int _w, _h;
	int _x, _y;
	int _tileWidth, _tileHeight;
	Color _bgColor;

	std::vector<Tileset *> _tilesets;
	std::vector<Layer * > _layers;

	Image _image;
};

inline void TileMap::move(int x, int y)
{
	_x += x; 
	_y += y;
}

inline int TileMap::getGid(int row, int colum)
{
	int position = row * _w + colum;
	int gid = 0;

	for(unsigned int i=0; i<_layers.size() && gid == 0; i++)
		gid = _layers[i]->getGid(position);

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
