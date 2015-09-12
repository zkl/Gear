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
}

bool TileMap::load(const char * file)
{
	XMLDocument document;
	document.LoadFile(file);
	XMLElement * root = document.FirstChildElement("map");
	if(root != 0)
	{
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

	_image.resize(_w*_tileWidth, _h*_tileHeight);
	SDL_FillRect(_image.surface(), 0, 
		SDL_MapRGB(_image.surface()->format, (Uint8)_bgColor.r(),(Uint8)_bgColor.g(), (Uint8)_bgColor.b()));
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

	_tilesets[name] = new Tileset(name, fgid, tileWidth, tileHeight, file);
}

void TileMap::anylyzeLayers(XMLElement * e)
{
	XMLElement * data = e->FirstChildElement("data");
	
	Layer * layer = new Layer(e->Attribute("name"));
	_layers.push_back(layer);

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
	};

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
		ImageLayer * layer = new ImageLayer(file);

		layer->move(x, y);
		layer->copy(_image.surface());
	}
}

Tileset * TileMap::getTileset(int gid)
{
	if(_tilesets.size() == 0 || gid <= 0)
		return 0;

	std::map<std::string, Tileset*>::iterator max = _tilesets.begin();
	std::map<std::string, Tileset*>::iterator it = _tilesets.begin();
	while(it != _tilesets.end())
	{
		if(gid < it->second->fgid())
			return --it->second;

		if(max->second->fgid() < it->second->fgid())
			max = it;

		it++;
	}

	return max->second;
}
void TileMap::drawlayer(Layer * layer)
{
	for(unsigned int i=0; i<_layers.size(); i++)
	{
		std::pair<int, int> p = _layers[i]->firstGid();
		while(p.second != 0)
		{
			Tileset * set = getTileset(p.second);	
			if(set)
			{
				set->copy(_image.surface(), ((p.first)%_w)*_tileWidth, 
					((p.first)/_w)*_tileHeight, p.second);
			}

			p = _layers[i]->nextGid();
		}
	}
}

void TileMap::draw(SDL_Renderer * renderer)
{
	_image.draw(renderer, _x, _y);

	Object::draw(renderer);
}
