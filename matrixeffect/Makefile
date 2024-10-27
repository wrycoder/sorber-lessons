
CC=clang
CFLAGS=-g -Wall -D_XOPEN_SOURCE_EXTENDED
OBJS=main.o matrix.o ui.o

all: main
	
main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lncursesw

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o main
