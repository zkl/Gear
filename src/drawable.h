#ifndef DRAW_ABLE_H
#define DRAW_ABLE_H


class Drawable 
{
public:
	~Drawable();

	virtual void draw(int x, int y);
};

inline Drawable::~Drawable()
{
}

inline void Drawable::draw(int x, int y)
{
}

#endif
