CC=gcc
CFLAGS= -W -Wall -pedantic
INCLUDE= ./include/
SRC= ./src/
OBJ=./obj/
PROGRAMS= app


OBJS = $(OBJ)clientAPI.o $(OBJ)snakeAPI.o $(OBJ)arena.o $(OBJ)snake.o $(OBJ)main.o

all: $(PROGRAMS)

$(PROGRAMS): $(OBJS)
	$(CC) -o $@ $^ -lm



$(OBJ)%.o:$(SRC)%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE) -lm



clean:
	rm -f $(OBJ)*.o *~ $(PROGRAMS)