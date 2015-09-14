#ifndef ASTAR_H
#define ASTAR_H

#include <map>
#include <vector>
#include <stdio.h>

class TileMap;

class Position
{
public:
	Position() : x(0), y(0), f(0), g(0), h(0), parent(0) {}
	int x, y, f;
	int g, h;
	Position* parent;
};

class AStar
{
public:
	AStar(int width = 0, int heighti = 0);

	void resize(int widht, int height);
	void begin (int x, int y);
	void target(int x, int y);

	bool find(TileMap* tilemap);
	std::vector<Position*>& way();

private:
	void clear();
	bool findOpenPosition(Position* position, TileMap* tilemap);
	int  getF(Position& position);
	int  getPositionID(Position* position);
	bool validPosition(Position* position);
	std::map<int, Position*>::iterator minF(std::map<int, Position*>& list);

	int _width;
	int _height;


	Position* _start; 
	Position* _stop;

	// y*_widht+x -> Position
	typedef std::map<int, Position*> PointContiner;
	PointContiner _opened;
	PointContiner _closeed;

	std::vector<Position*> _path;
};

inline std::vector<Position*>& AStar::way()
{
	return _path;
}

inline int AStar::getPositionID(Position* position)
{
	return position->x*_width + position->y;
}

#endif
