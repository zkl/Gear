#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "tileset.h"

class Layer 
{
public:
	Layer();

	int setGid(int postion, int gid);
	int getGid(int postion);

	std::pair<int, int> nextGid();
	std::pair<int, int> firstGid();

private:

	std::string _name;
	std::map<int, int>::iterator _it;
	std::map<int, int> _data;
};

#endif
