INCLUDE_PATHS = -I/opt/homebrew/include -I/opt/homebrew/include/chipmunk -I/opt/homebrew/include/SDL2
LIBRARY_PATHS = -L/opt/homebrew/lib

all:
	gcc atoms.c physics.c init.c collision.c -o atoms $(INCLUDE_PATHS) $(LIBRARY_PATHS) -lchipmunk -lSDL2 -lSDL2_image -lSDL2_ttf
