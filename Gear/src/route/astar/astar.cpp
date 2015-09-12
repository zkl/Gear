#include "astar.h"

AStar::AStar(int width, int height) :
	_width(width),
	_height(height)
{
}

void AStar::setStart(int x, int y)
{
	_start = x*_width + y;
}

void AStar::setStop (int x, int y)
{
	_stop = x*_width + y;
}

// path: out param
bool AStar::find(std::vector<int, int>& path, TileMap* tilemap)
{

	return true;
}

