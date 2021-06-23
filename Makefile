FLAGS=-lSDL2 -lSDL2_image

geary-guy.x86_64: main.c
	gcc $? $(FLAGS) -o $@
