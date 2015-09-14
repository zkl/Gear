
VPATH = ../../../src  ../../../src/tilemap ../../../src/route/astar \
	../src

OBJECTS = sprite.o runner.o world.o object.o objectpool.o tilemap.o color.o\
	layer.o tileset.o imagelayer.o spritesheet.o sdlgame.o image.o \
	movie.o astar.o main.o gamescreen.o tank.o bullet.o

CPPFLAGS += -g -I../../../

tank : $(OBJECTS)
	g++ -o $@ $(OBJECTS) `pkg-config --cflags --libs sdl2 SDL2_image tinyxml2` -lSDL2_gfx

clean : 
	rm -rf $(OBJECTS)
