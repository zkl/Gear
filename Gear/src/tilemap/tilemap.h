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
	void move(int x, int y){_x+=x; _y+=y;}
	virtual void draw(SDL_Renderer * renderer);

private:
	void initSurface(tinyxml2::XMLElement * root);
	void getTileset(tinyxml2::XMLElement * e);
	void getLayers(tinyxml2::XMLElement * e);
	void drawlayer(Layer * layer);
	void getImageLayer(tinyxml2::XMLElement * e);

	Tileset * getTilesetContainGid(int gid);

	int _w, _h;
	int _x, _y;
	int _tileWidth, _tileHeight;
	Color _dftclr;

	std::vector<Tileset *> _tilesets;
	std::vector<Layer * > _layers;

	Image _image;
};

#endif
