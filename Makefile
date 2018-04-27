#CC=gcc
CFLAGS   = -Wall -Wextra -mtune=native `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm

debug:helper.c main.c
	$(CC) $(CFLAGS) -g $? -o parallax $(LDFLAGS)
stable:helper.c main.c
	$(CC) $(CFLAGS) $? -o parallax $(LDFLAGS)
clean:
	rm -vfr *~ parallax
