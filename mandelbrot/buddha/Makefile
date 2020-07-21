CC = gcc
CXX = g++
CFLAGS = -O2 -std=c99 -pedantic -Werror
CXXFLAGS = -O2 -std=c++11 -pedantic -Werror
LFLAGS = -lm

all: buddhabrot buddhabrotpp

buddhabrot: buddhabrot.o
	$(CC) -o $@ $^ $(LFLAGS)

buddhabrot.o : buddhabrot.c
	$(CC) $(CFLAGS) -c $<

buddhabrotpp: buddhabrotpp.o
	$(CXX) -o $@ $^ $(LFLAGS)

buddhabrotpp.o : buddhabrotpp.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o buddhabrot buddhabrotpp
