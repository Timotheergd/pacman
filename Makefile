# A simple Makefile

# set the compiler
CC := gcc

# set the compiler flags
CFLAGS := `sdl2-config --libs --cflags` -lSDL2_image -lSDL2_ttf

# name of executable
EXEC := pacman

# recipe to clean the workspace
clean:
	@ rm -f $(EXEC) $(OBJS)

compile:
	$(CC) *.c -o $(EXEC) $(CFLAGS)

# compile and run
run:
	./$(EXEC)

# clear the terminal
clear:
	clear

all: clear compile run clean