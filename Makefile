LDLIBS=$(shell sdl-config --libs --cflags) -lSDL_gfx

all: example

clean:
	rm -rf example

