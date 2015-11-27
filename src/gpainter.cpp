#include "gpainter.h"
#include "gimage.h"

void GPainter::draw(const GImage& image, int x, int y)
{
	if(image._surface == 0 || _image->_surface == 0)
		return ;

	int w = image._surface->w;
	int h = image._surface->h;

	SDL_Rect desrect;
	SDL_Rect srcrect;

	desrect.x = 0;
	desrect.y = 0;
	desrect.w = w;
	desrect.h = h;

	srcrect.x = x;
	srcrect.y = y;
	srcrect.w = w;
	srcrect.h = h;

	SDL_BlitSurface(image._surface, &srcrect, _image->_surface, &desrect);
}
