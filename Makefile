define colorecho
      @tput setaf 2
      @echo $1
      @tput sgr0
endef

CC=gcc
CFLAGS   = -Wall -Wextra -mtune=native -no-pie `sdl2-config --cflags`
LDFLAGS  = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx -lm

TARGETS = parallax

.PHONY: all
all: $(TARGETS)

parallax: helper.c parallax.c
	@cc $(CFLAGS) -o $@ $+ $(LDFLAGS)
	$(call colorecho,"$@ success. ./\"$@\" to execute.")

.PHONY: clean
clean:
	@rm $(TARGETS) 2>/dev/null || true
	$(call colorecho,"It is clean now.")

# hot compile
# while inotifywait -e close_write ./parallax.c; do date +%X; make > /dev/null; done
# kill -9 $(pidof parallax)
# $<	first dependency
# $@	target name
# $+	list of all dependencies
# $^	list of all unique dependencies


