

CC=clang
CFLAGS=-Wall -g
EXE=readonly


all: $(EXE)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)

clean:
	rm -rf *.dSYM *.o $(EXE)
