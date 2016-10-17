pvz:	main.c
	gcc -Wall -Wextra -g  main.c tools.c `sdl-config --cflags --libs` -lm -o svz

clean:
	rm svz
