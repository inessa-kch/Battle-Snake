
CC=gcc
CFLAGS= -W -Wall -pedantic
INCLUDE= ./include/
PROGRAMS= app

all: $(PROGRAMS)



app: clientAPI.o  snakeAPI.o main.o
	$(CC) -o $@ $^


%.o:%.c
	$(CC) -o $@ -c $< $(CFLAGS) 



clean:
	rm -f *.o *~ $(PROGRAMS)