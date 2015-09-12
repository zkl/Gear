#ifndef ASTAR_H
#define ASTAR_H

#include <map>
#include <vector>

class TileMap;

class AStar
{
public:
	AStar(int width, int height);

	void setStart(int x, int y);
	void setStop (int x, int y);
	bool find(std::vector<int, int>& path, TileMap* tilemap);

private:
	int _width;
	int _height;

	// position = x*width + y;
	typedef int Position;

	Position _start; 
	Position _stop;

	// F -> position
	std::map<int, Position> _opened;
	std::map<int, Position> _closeed;
};

#endif
