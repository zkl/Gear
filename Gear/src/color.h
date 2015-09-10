#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color 
{
public:
	Color() {_color.r = 0; _color.g = 0; _color.b = 0; _color.a = 0;}
	unsigned short r();
	unsigned short g();
	unsigned short b();
	unsigned short a();

	int toint();
	bool fromString(const std::string & colorstr);
	std::string tostring();

private:
	struct _ColorDef
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
	
	_ColorDef _color;
};

#endif
