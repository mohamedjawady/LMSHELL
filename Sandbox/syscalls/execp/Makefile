.PHONY: clean run

PROGRAMS = execp

all: $(PROGRAMS)

$(PROGRAMS): $(PROGRAM=$(.TARGET))

CC = gcc
CFLAGS = -Wno-implicit-function-declaration

clean:
	rm `find . -type f -executable | xargs`

$(PROGRAM): $(PROGRAM).c
	$(CC) -o $(.TARGET) $(CFLAGS)
	
