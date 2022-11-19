.PHONY: clean run

PROGRAMS = wait

all: $(PROGRAMS)

$(PROGRAMS): $(PROGRAM=$(.TARGET))

CC = gcc
CFLAGS = -Wno-implicit-function-declaration

clean:
	rm `find . -type f -executable | xargs`

$(PROGRAM): $(PROGRAM).c
	$(CC) -o $(.TARGET) $(CFLAGS)
	