CC = gcc
CXX = g++
CFLAGS = -O2 -pedantic-errors -Wall
LFLAGS = -lm

all: bbrot bbrotpp

bbrot: bbrot.o
	$(CC) -o $@ $^ $(LFLAGS)

bbrot.o : bbrot.c
	$(CC) $(CFLAGS) -c $<

bbrotpp: bbrotpp.o
	$(CXX) -o $@ $^ $(LFLAGS)

bbrotpp.o : bbrotpp.cpp
	$(CXX) $(CFLAGS) -c $<

clean:
	rm -f bbrot.o bbrot bbrotpp.o bbrotpp
