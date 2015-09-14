#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "color.h"


unsigned short Color::r()
{
	return _color.r;
}

unsigned short Color::g()
{
	return _color.g;
}

unsigned short Color::b()
{
	return _color.b;
}

unsigned short Color::a()
{
	return _color.a;
}

int Color::toint()
{
	return *(int*)(&_color);
}

bool Color::fromString(const std::string & colorstr)
{
	if(colorstr.size() < 6)
		return false;
	
	_color.r = (unsigned char)strtol(colorstr.substr(1, 2).c_str(), 0, 16);
	_color.g = (unsigned char)strtol(colorstr.substr(3, 2).c_str(), 0, 16);
	_color.b = (unsigned char)strtol(colorstr.substr(5, 2).c_str(), 0, 16);

	if(colorstr.size() > 7)
		_color.a = (unsigned char)strtol(colorstr.substr(7, 2).c_str(), 0, 16);

	return true;
}

std::string Color::tostring()
{
	char buf[32];
	sprintf(buf, "#%2x%2x%2x%2x", _color.r, _color.g, _color.b, _color.a);
	return std::string(buf);
}
