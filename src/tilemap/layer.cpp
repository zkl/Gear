#include "layer.h"

Layer::Layer()
{
	_it = _data.begin();
}

int Layer::setGid(int postion, int gid)
{
	int ogid = 0;
	std::map<int, int>::iterator it = _data.find(postion);
	if(it != _data.end())
	{
		ogid = it->second;
		if(gid != 0)
			it->second = gid;
		else
			_data.erase(it);
	}
	else if(gid != 0)
	{
		_data[postion] = gid;
	}

	return ogid;
}

int Layer::getGid(int postion)
{
	int gid = 0;
	
	std::map<int, int>::iterator it = _data.find(postion);
	if(it != _data.end())
		gid = it->second;

	return gid;
}

std::pair<int, int> Layer::firstGid()
{
	if(_data.size() == 0)
		return std::make_pair(0, 0);

	_it = _data.begin();
	return *_it++;
}

std::pair<int, int> Layer::nextGid()
{
	if(_it == _data.end())
		return std::make_pair(0, 0);

	return *_it++;
}

