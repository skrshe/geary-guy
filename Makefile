FLAGS=-lSDL2 -lSDL2_image -lm -ggdb

gg: main.c
	gcc $? $(FLAGS) -o $@

clean:
	rm -rf gg

run:
	./out/tux64/gg
