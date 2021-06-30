FLAGS=-lSDL2 -lSDL2_image -lm -ggdb

geary-guy.x64: main.c
	gcc $? $(FLAGS) -o $@

clean:
	rm -rf geary-guy.x64

run:
	./geary-guy.x64
