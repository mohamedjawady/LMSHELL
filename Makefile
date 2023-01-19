OBJS	= main.o utils/lm_builtins.o utils/lm_file.o utils/lm_modes.o utils/lm_process.o utils/lm_wrappers.o utils/parser.o
SOURCE	= main.c utils/lm_builtins.c utils/lm_file.c utils/lm_modes.c utils/lm_process.c utils/lm_wrappers.c utils/parser.c
HEADER	= utils/constants.h utils/lm_builtins.h utils/lm_file.h utils/lm_modes.h utils/lm_process.h utils/lm_wrappers.h utils/parser.h
OUT	= lmshell
CC	 = gcc
FLAGS	 = -g -c
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c -o main.o

utils/lm_builtins.o: utils/lm_builtins.c
	$(CC) $(FLAGS) utils/lm_builtins.c -o utils/lm_builtins.o

utils/lm_file.o: utils/lm_file.c
	$(CC) $(FLAGS) utils/lm_file.c -o utils/lm_file.o

utils/lm_modes.o: utils/lm_modes.c
	$(CC) $(FLAGS) utils/lm_modes.c -o utils/lm_modes.o

utils/lm_process.o: utils/lm_process.c
	$(CC) $(FLAGS) utils/lm_process.c -o utils/lm_process.o

utils/lm_wrappers.o: utils/lm_wrappers.c
	$(CC) $(FLAGS) utils/lm_wrappers.c -o utils/lm_wrappers.o

utils/parser.o: utils/parser.c
	$(CC) $(FLAGS) utils/parser.c -o utils/parser.o


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)