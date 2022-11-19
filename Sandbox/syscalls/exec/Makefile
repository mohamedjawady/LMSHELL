.PHONY: clean run

PROGRAMS = execMain execForeign

all: $(PROGRAMS)

$(PROGRAMS): $(PROGRAM=$(.TARGET))

CC = gcc

clean:
	rm `find . -type f -executable | xargs`

$(PROGRAM): $(PROGRAM).c
	$(CC) -o $(.TARGET)
	
