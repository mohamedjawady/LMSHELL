CC=gcc
CFLAGS=-I.
DEPS = hellomake.h

OBJ_PATH = ./obj
OBJ = hellomake.o hellofunc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $(OBJ_PATH)/* $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $(OBJ_PATH)/* $(CFLAGS)
