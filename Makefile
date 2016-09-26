pvz:	main.c
	gcc -Wall -g  main.c `sdl-config --cflags --libs` -lm -o pvz

clean:
	rm pvz
