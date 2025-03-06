CC=gcc
CPP=g++
CFLAGS=-Wall -g
CPPFLAGS=-Wall -g -std=c++17
BINS=example

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

%: %.cpp
	$(CPP) $(CPPFLAGS) $< -o $@

clean:
	$(RM) -r *.dSYM
	$(RM) *.o $(BINS)
