#include <stdlib.h>
#include "tilemap.h"

TileMap::TileMap() : 
	_w(0), 
	_h(0), 
	_x(0), 
	_y(0), 
	_tileWidth(0), 
	_tileHeight(0)
{
}

TileMap::~TileMap()
{
	this->clear();
}

void TileMap::clear()
{
	for(std::map<std::string, Layer * >::iterator it = _layers.begin(); it != _layers.end(); it++)
		delete it->second;

	for(std::map<std::string, Tileset*>::iterator it = _tilesets.begin(); it!= _tilesets.end(); it++)
		delete it->second;

	_layers.clear();
	_tilesets.clear();
	_objects.clear();
}

bool TileMap::load(const char * file)
{
	this->clear();

	XMLDocument document;
	document.LoadFile(file);
	XMLElement * root = document.FirstChildElement("map");
	if(root != 0)
	{
		// base path
		strcpy(_basePath, file);
		char* p = &_basePath[strlen(file)-1];
		while(p != _basePath && *p != '/')
			p--;

		if(*p == '/')
			*p = 0;

		//_splitpath(file, 0, _basePath, 0, 0);

		analyzeMapInfo(root);
		for(XMLElement* e = root->FirstChildElement(); e != 0; 
			e = e->NextSiblingElement())
		{
			if(e->Value() == std::string("tileset"))
				this->analyzeTileset(e);
			else if(e->Value() == std::string("layer"))
				this->anylyzeLayers(e);
			else if(e->Value() == std::string("imagelayer"))
				this->anylyzeImageLayer(e);
		}
		return true;
	}
	return false;
}

void TileMap::analyzeMapInfo(tinyxml2::XMLElement * root)
{
	_w = atoi(root->Attribute("width"));
	_h = atoi(root->Attribute("height"));
	_tileWidth = atoi(root->Attribute("tilewidth"));
	_tileHeight = atoi(root->Attribute("tileheight"));

	const char * color = root->Attribute("backgroundcolor");
	_bgColor.fromString(color);

	_objects.resize(_w*_h);
	_image.resize(_w*_tileWidth, _h*_tileHeight);
	_image.fill(&_bgColor);
}

void TileMap::analyzeTileset(XMLElement * e)
{
	const char * name = 0;
	const char * file = 0;
	int fgid;
	int tileWidth, tileHeight;

	name = e->Attribute("name");
	
	fgid = atoi(e->Attribute("firstgid"));
	tileWidth = atoi(e->Attribute("tilewidth"));
	tileHeight = atoi(e->Attribute("tileheight"));

	XMLElement * ie = e->FirstChildElement("image");
	if(ie != 0)
		file = ie->Attribute("source");

	char tilefile[1024];
	strcpy(tilefile, _basePath);
	strcat(tilefile, "/");
	strcat(tilefile, file);
	_tilesets[name] = new Tileset(name, fgid, tileWidth, tileHeight, tilefile);
}

void TileMap::anylyzeLayers(XMLElement * e)
{
	XMLElement * data = e->FirstChildElement("data");
	
	const char* name = e->Attribute("name");
	if(name == 0)
	{
		SDL_Log("TileMap::anylyzeLayers erro");
		return ;
	}

	Layer * layer = new Layer();
	_layers[name] = layer;

	if(data != 0)
	{
		const char * d = data->GetText();
		int i=0;
		while(*d)
		{
			int gid = atoi(d);
			if(gid != 0)
				layer->setGid(i, gid);

			++i;
			const char* p = strchr(d, ',');
			if(p != 0)
				d = p+1;
			else
				d = strlen(d) + d;

			if(*d == ' ')
				d++;
			else if(*d == '\n')
				d++;
		};
	}
	else
	{
		return ;
	}

	drawlayer(layer);
}

void TileMap::anylyzeImageLayer(XMLElement * e)
{
	int x = 0, y = 0;
	const char * v;

	if((v = e->Attribute("x")) != 0)
		x = atoi(v);
	
	if((v = e->Attribute("y")) != 0)
		y = atoi(v);

	tinyxml2::XMLElement * data = e->FirstChildElement("image");

	if(data != 0)
	{
		const char * file = data->Attribute("source");


		char imageFile[1024];
		strcpy(imageFile, _basePath);
		strcat(imageFile, "/");
		strcat(imageFile, file);
		ImageLayer * layer = new ImageLayer(imageFile);

		layer->move(x, y);
		layer->copy(_image.surface());
	}
}

Tileset * TileMap::findTilesetByGid(int gid)
{
	if(_tilesets.size() == 0 || gid <= 0)
		return 0;

	std::map<std::string, Tileset*>::iterator it  = _tilesets.begin();
	while(it != _tilesets.end())
	{
		if(gid >= it->second->minGid() && gid < it->second->maxGid())
			return it->second;

		it++;
	}

	return 0;
}
void TileMap::drawlayer(Layer * layer)
{
	//for(std::map<std::string, Layer*>::iterator it = _layers.begin(); it!=_layers.end(); it++)
	//{
	//	Layer* layer = it->second;
		std::pair<int, int> p = layer->firstGid();
		while(p.second != 0)
		{
			Tileset * set = findTilesetByGid(p.second);	
			if(set)
			{
				set->copy(_image.surface(), ((p.first)%_w)*_tileWidth, 
					((p.first)/_w)*_tileHeight, p.second);
			}

			p = layer->nextGid();
		}
	//}
	_image.update();
}

void TileMap::draw(SDL_Renderer * renderer)
{
	_image.draw(renderer, _x, _y);

	Object::draw(renderer);
}

bool TileMap::setGid(int x, int y, int gid)
{
	if(_layers.size() <= 0)
		return false;

	SDL_Rect rect;
	rect.x = x/_tileWidth * _tileWidth;
	rect.y = y/_tileHeight* _tileHeight;
	rect.w = _tileWidth;
	rect.h = _tileHeight;
 	_image.fill(&_bgColor, &rect);

	int position = x/_tileWidth + y/_tileHeight*_w;

	Layer* layer = _layers.begin()->second;
	layer->setGid(position, gid);

	Tileset * tileset = findTilesetByGid(gid);	
	if(tileset && gid != 0)
		tileset->copy(_image.surface(), rect.x, rect.y, gid);

	return true;
}
