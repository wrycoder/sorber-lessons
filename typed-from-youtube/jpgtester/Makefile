CC=clang
CFLAGS=-Wall -g
EXE=jpgtester

all: $(EXE)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.dSYM *.o $(EXE)
