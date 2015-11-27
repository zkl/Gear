#ifndef G_PAINTER_H
#define G_PAINTER_H

class GPainter
{
	friend class GImage;

public:
	void draw(const GImage& image, int x, int y);

private:
	GPainter(GImage* image);

	GImage* _image;
};

inline GPainter::GPainter(GImage* image) : _image(image)
{
}

#endif