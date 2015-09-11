
VPATH = ../../Gear/src  ../../Gear/src/tilemap ../../Gear/robot

OBJECTS = sprite.o runner.o world.o object.o objectpool.o tilemap.o color.o\
	layer.o tileset.o imagelayer.o spritesheet.o sdlgame.o image.o \
	movie.o main.o gamescreen.o robot.o

CPPFLAGS += -g

robot : $(OBJECTS)
	g++ -o $@ $(OBJECTS) `pkg-config --cflags --libs sdl2 SDL2_image tinyxml2` -lSDL2_gfx

clean : 
	rm -rf $(OBJECTS)
