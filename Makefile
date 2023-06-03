CC = gcc -Wall -Werror -Wextra -g -O2
GTKCFLAGS = $(shell pkg-config --cflags gtk4)
GTKLIBS = $(shell pkg-config --libs gtk4)
MATHCORELIB = -Ilibs/mathCore/headers
GUILIB = -Ilibs/GUI/headers
UTILSLIB= -Ilibs/utils/headers

all: main

main: GUI
	$(CC) $(GUILIB) -o main main.c object_files/math.o object_files/GUI.o object_files/utils.o -lm $(GTKLIBS)

GUI: mathCore utils
	$(CC) -c $(GTKCFLAGS) $(MATHCORELIB) $(UTILSLIB) -o GUI.o libs/GUI/GUI.c $(GTKLIBS)
	mv GUI.o object_files

utils:
	$(CC) -c -o utils.o libs/utils/utils.c
	mv utils.o object_files

mathCore:
	$(CC) -c libs/mathCore/mathCore.c -o math.o
	mv math.o object_files

clean:
	rm -rf object_files/*.o
