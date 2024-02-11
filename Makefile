# A simple Makefile

# set the compiler
CC := gcc

# source files path
SRC_DIRS := ./src

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -lSDL2_image -lSDL2_ttf -lm

# name of executable
EXEC := pacman

clean:
	@ rm -f $(EXEC)

compile:
	$(CC) main.c $(SRC_DIRS)/*.c -o $(EXEC) $(CFLAGS)

run:
	./$(EXEC)

# clear the terminal
clear:
	clear

all: clear compile run clean