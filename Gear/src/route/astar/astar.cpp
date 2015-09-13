#include <stdio.h>
#include "astar.h"
#include "../../tilemap/tilemap.h"

AStar::AStar(int width, int height) :
	_width(width),
	_height(height),
	_start(0),
	_stop(0)
{
}

void AStar::resize(int widht, int height)
{
	_width = widht;
	_height = height;
}

void AStar::begin(int x, int y)
{
	this->clear();
	
	if(_start == 0)
		_start = new Position();

	_start->x = x;
	_start->y = y;
}

void AStar::target(int x, int y)
{
	this->clear();

	if(_stop == 0)
		_stop = new Position();

	_stop->x = x;
	_stop->y = y;
}

void AStar::clear()
{
	if(_closeed.size() == 0) // not find
		return ;

	PointContiner::iterator it;
	for(it = _opened.begin(); it != _opened.end(); it++)
		delete it->second;

	for(it = _closeed.begin(); it != _closeed.end(); it++)
		delete it->second;

	_path.clear();
	_opened.clear();
	_closeed.clear();

	// _start in opened list;
	delete _stop;

	_start = 0;
	_stop  = 0;
}

// path: out param
bool AStar::find(TileMap* tilemap)
{
	this->clear();
	if(_start == 0 || _stop == 0)
		return false;
	
	// insert _start
	_opened[getPositionID(_start)] = _start;

	Position* point = 0;
	while(_opened.size() > 0)
	{
		PointContiner::iterator it = minF(_opened);
		point  = it->second;
		_closeed[it->first] = it->second;
		_opened.erase(it);

		if(findOpenPosition(point, tilemap)) // find stop;
		{
			point = _stop;
			while(point && point->parent != 0)
			{
				_path.insert(_path.begin(), point);
				point = point->parent;
			}
			return true;
		}
	}

	return false;
}

bool AStar::findOpenPosition(Position* position, TileMap* tilemap)
{
	int gid = 0;
	Position* p = new Position();
	int f = 0;

	if(position->x == _stop->x && position->y == _stop->y)
	{
		_stop->parent = position;
		return true;
	}

	p->parent = position;
	p->g = position->g+1;
	p->x = position->x+1;
	p->y = position->y;
	p->f  = getF(*p);
	f = p->y*_width+p->x;
	if(p->x < _width && tilemap->getGridGid(p->x, p->y) == 0 && _closeed.find(f) == _closeed.end())
	{
		_opened[f] = p;
		if(p->x == _stop->x && p->y == _stop->y)
		{
			_stop->parent = p;
			return true;
		}
		
		p = 0;
	}

	if(p == 0)
		p = new Position();

	p->parent = position;
	p->g = position->g+1;
	p->x = position->x-1;
	p->y = position->y;
	p->f  = getF(*p);
	f = p->y*_width+p->x;
	if(p->x >= 0 && tilemap->getGridGid(p->x, p->y) == 0 && _closeed.find(f) == _closeed.end())
	{
		_opened[f] = p;
		if(p->x == _stop->x && p->y == _stop->y)
		{
			_stop->parent = p;
			return true;
		}
		p = 0;
	}

	if(p == 0)
		p = new Position();

	p->parent = position;
	p->g = position->g+1;
	p->x = position->x;
	p->y = position->y+1;
	p->f  = getF(*p);
	f = p->y*_width+p->x;
	if(p->y < _height && tilemap->getGridGid(p->x, p->y) == 0 && _closeed.find(f) == _closeed.end())
	{
		_opened[f] = p;
		if(p->x == _stop->x && p->y == _stop->y)
		{
			_stop->parent = p;
			return true;
		}
		p = 0;
	}

	if(p == 0)
		p = new Position();
	
	p->parent = position;
	p->g = position->g+1;
	p->x = position->x;
	p->y = position->y-1;
	p->f  = getF(*p);
	f = p->y*_width+p->x;
	if(p->y >= 0 && tilemap->getGridGid(p->x, p->y) == 0 && _closeed.find(f) == _closeed.end())
	{
		_opened[f] = p;
		if(p->x == _stop->x && p->y == _stop->y)
		{
			_stop->parent = p;
			return true;
		}
		p = 0;
	}

	/*
	if(p == 0)
		p = new Position();

	p->parent = position;
	p->x = position->x+1;
	p->y = position->y+1;
	p->f  = getF(*p);
	f = p->y*_width+p->x;
	if(p->x <= _width && p->y <= _height && tilemap->getGridGid(p->x, p->y) == 0 && _closeed.find(f) == _closeed.end())
	{	
		_opened[f] = p;
		if(p->x == _stop.x && p->y == _stop.y)
		{
			_stop.parent = p;
			return true;
		}
		p = 0;
	}

	if(p == 0)
		p = new Position();

	p->parent = position;
	p->x = position->x+1;
	p->y = position->y-1;
	p->f  = getF(*p);
	f = p->y*_width+p->x;
	if(p->x <= _width && p->y >= 0 && tilemap->getGridGid(p->x, p->y) == 0 && _closeed.find(f) == _closeed.end())
	{
		_opened[f] = p;
		if(p->x == _stop.x && p->y == _stop.y)
		{
			_stop.parent = p;
			return true;
		}
		p = 0;
	}

	if(p == 0)
		p = new Position();

	p->parent = position;
	p->x = position->x-1;
	p->y = position->y-1;
	p->f  = getF(*p);
	f = p->y*_width+p->x;
	if(p->x >= 0 && p->y >= 0 && tilemap->getGridGid(p->x, p->y) == 0 && _closeed.find(f) == _closeed.end())
	{
		_opened[f] = p;
		if(p->x == _stop.x && p->y == _stop.y)
		{
			_stop.parent = p;
			return true;
		}
		 p = 0;
	}

	if(p == 0)
		p = new Position();

	p->parent = position;
	p->x = position->x-1;
	p->y = position->y+1;
	p->f  = getF(*p);
	f = p->y*_width+p->x;
	if(p->x >= 0 && p->y <= _height && tilemap->getGridGid(p->x, p->y) == 0 && _closeed.find(f) == _closeed.end())
	{
		_opened[f] = p;
		if(p->x == _stop.x && p->y == _stop.y)
		{
			_stop.parent = p;
			return true;
		}
		p = 0;
	}

	*/
	if(p != 0)
		delete p;
	return false;
}

std::map<int, Position*>::iterator AStar::minF(std::map<int, Position*>& list)
{
	std::map<int, Position*>::iterator min = list.begin();
	std::map<int, Position*>::iterator it  = list.begin();
	while(++it != list.end())
	{
		if(min->second->f > it->second->f)
			min = it;
	}

	return min;
}

int AStar::getF(Position& position)
{
	int g = abs(position.x-_start->x)+abs(position.y-_start->y);
	int f = abs(position.x-_stop->x) + abs(position.y-_stop->y) + position.g + g;
	return f;
}

bool AStar::validPosition(Position* position)
{
	if(position->x >= 0 && position->x < _width &&
		position->y >= 0 && position->y < _height)
		return true;
		
	return false;
}
